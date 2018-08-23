//
// Created by lvjiaming on 2018/8/14.
//
#include <render/cube/Cube.h>
#include <Config.h>
#include <loader/Loader.h>

Cube::Cube(const glm::vec3 &position)
:  _glProgram(nullptr)
, _diffuseTextureId(0)
, _specularTextureId(0)
, _materialType(Cube::MaterialType::COLOR)
, _capacityPointLight(0)
, _spotLight(nullptr)
, _pointLightDirty(false)
, _spotLightDirty(false)
{
    init();
    setPosition(position);
}

Cube::~Cube() {
    delete _glProgram;
    _diffuseTextureId = 0;
    _specularTextureId = 0;
    _capacityPointLight = 0;
    _pointLight.resize(0);
}

void Cube::init() {
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_N3F_T2F_C4F) * VERTICES_NUMBER, _bufferGLCube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_N3F_T2F_C4F), (void *)offsetof(V3F_N3F_T2F_C4F, vertices));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_N3F_T2F_C4F), (void *)offsetof(V3F_N3F_T2F_C4F, normals));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_N3F_T2F_C4F), (void *)offsetof(V3F_N3F_T2F_C4F, texCoords));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_N3F_T2F_C4F), (void *)offsetof(V3F_N3F_T2F_C4F, colors));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _glProgram = new Shader(cube_vertexShaderSource, cube_fragmentShaderSource);

    _pointLight.resize(POINT_LIGHT_NUMBER);

}

void Cube::setColor(const Color4F &color) {
    for (auto &vertex : _bufferGLCube) {
        vertex.colors = color;
    }
    _dirty = true;
}

void Cube::setMaterial(const std::string &diffusePath, const std::string &specularPath, float shininess) {
    _diffuseTextureId = Loader::getInstance()->loadTexture(diffusePath).textureId;
    _specularTextureId = Loader::getInstance()->loadTexture(specularPath).textureId;
    _shininess = shininess;
    _materialType = MaterialType::TEXTURE;

    _glProgram->use();
    _glProgram->setInt("textureMaterial.diffuse", 0);
    _glProgram->setInt("textureMaterial.specular", 1);
    _glProgram->setFloat("textureMaterial.shininess", _shininess);
    _glProgram->setInt("materialType", _materialType);
}

void Cube::setMaterial(const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor, const glm::vec3 &specularColor, float shininess) {
    _ambientColor = ambientColor;
    _diffuseColor = diffuseColor;
    _specularColor = specularColor;
    _shininess = shininess;
    _materialType = MaterialType::COLOR;

    _glProgram->use();
    _glProgram->setVec3("colorMaterial.ambient", _ambientColor);
    _glProgram->setVec3("colorMaterial.diffuse", _diffuseColor);
    _glProgram->setVec3("colorMaterial.specular", _specularColor);
    _glProgram->setFloat("colorMaterial.shininess", _shininess);
    _glProgram->setInt("materialType", _materialType);
}

void Cube::addDirectionLight(const DirectionLight *directionLight) {
    _directionLight = directionLight;

    _glProgram->use();
    _glProgram->setVec3("dirLight.direction", _directionLight->getDirection());
    _glProgram->setVec3("dirLight.ambient", _directionLight->getAmbient());
    _glProgram->setVec3("dirLight.diffuse", _directionLight->getDiffuse());
    _glProgram->setVec3("dirLight.specular", _directionLight->getSpecular());
}

void Cube::addPointLight(const PointLight *pointLight) {
    if (_capacityPointLight < POINT_LIGHT_NUMBER) {
        _pointLight[_capacityPointLight] = pointLight;
        _capacityPointLight++;
        _pointLightDirty = true;

    } else {
        printf("No more point light.");
    }

}

void Cube::addSpotLight(const SpotLight *spotLight) {
    _spotLight = spotLight;
    _spotLightDirty = true;
}

void Cube::setPosition(const glm::vec3 &position) {
    _position = glm::mat4();
    _position = glm::translate(_position, position);
}

void Cube::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    if (_dirty) {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_N3F_T2F_C4F) * VERTICES_NUMBER, _bufferGLCube, GL_STATIC_DRAW);
        _dirty = false;
    }

    if (_diffuseTextureId) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTextureId);
    }
    if (_specularTextureId) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _specularTextureId);
    }

    _glProgram->use();
    _glProgram->setMat4("model", _position);
    _glProgram->setMat4("view", view);
    _glProgram->setMat4("projection", projection);
    _glProgram->setVec3("viewPos", viewPos);



    // point light
    if (_pointLightDirty) {
        char tmp[100];
        for (size_t index = 0; index < _capacityPointLight; index++) {

            // sprintf(tmp, "pointLights[%lu].position", index);
            _glProgram->setVec3("pointLights[" + std::to_string(index) + "].position", _pointLight[index]->getPosition());

            sprintf(tmp, "pointLights[%lu].ambient", index);
            _glProgram->setVec3(tmp, _pointLight[index]->getAmbient());

            sprintf(tmp, "pointLights[%lu].diffuse", index);
            _glProgram->setVec3(tmp, _pointLight[index]->getDiffuse());

            sprintf(tmp, "pointLights[%lu].specular", index);
            _glProgram->setVec3(tmp, _pointLight[index]->getSpecular());

            sprintf(tmp, "pointLights[%lu].constant", index);
            _glProgram->setFloat(tmp, _pointLight[index]->getConstant());

            sprintf(tmp, "pointLights[%lu].linear", index);
            _glProgram->setFloat(tmp, _pointLight[index]->getLinear());

             sprintf(tmp, "pointLights[%lu].quadratic", index);
            _glProgram->setFloat(tmp, _pointLight[index]->getQuadratic());

        }
        _glProgram->setInt("pointLightNumber", (int) _capacityPointLight);
        _pointLightDirty = false;
    }

    // spot light
    if(_spotLight && _spotLightDirty) {
        _glProgram->setVec3("spotLight.position", _spotLight->getPosition());
        _glProgram->setVec3("spotLight.direction", _spotLight->getDirection());
        _glProgram->setFloat("spotLight.cutOff", _spotLight->getCutOff());
        _glProgram->setFloat("spotLight.outerCutOff", _spotLight->getOuterCutOff());
        _glProgram->setFloat("spotLight.constant", _spotLight->getConstant());
        _glProgram->setFloat("spotLight.linear", _spotLight->getLinear());
        _glProgram->setFloat("spotLight.quadratic", _spotLight->getQuadratic());
        _glProgram->setVec3("spotLight.ambient", _spotLight->getAmbient());
        _glProgram->setVec3("spotLight.diffuse", _spotLight->getDiffuse());
        _glProgram->setVec3("spotLight.specular", _spotLight->getSpecular());
        _spotLightDirty = false;
    }

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, VERTICES_NUMBER);
    glBindVertexArray(0);
}