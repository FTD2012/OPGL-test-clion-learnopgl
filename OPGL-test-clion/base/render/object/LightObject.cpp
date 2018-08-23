//
// Created by lvjiaming on 2018/8/21.
//

#include <render/object/LightObject.h>
#include <Config.h>
#include <loader/Loader.h>

LightObject::LightObject(const glm::vec3 &position)
:  _glProgram(nullptr)
, _diffuseTextureId(0)
, _specularTextureId(0)
, _materialType(LightObject::MaterialType::COLOR)
, _capacityPointLight(0)
, _spotLight(nullptr)
, _pointLightDirty(false)
, _spotLightDirty(false)
{
    init();
    setPosition(position);
}

LightObject::LightObject(const std::string &diffusePath, const std::string &specularPath, float shininess, const glm::vec3 &position)
: LightObject(position)
{
    setMaterial(diffusePath, specularPath, shininess);
}

LightObject::~LightObject() {
    delete _glProgram;
    _glProgram = nullptr;
    _diffuseTextureId = 0;
    _specularTextureId = 0;
    _capacityPointLight = 0;
    _pointLight.resize(0);
}

bool LightObject::init() {
    _pointLight.resize(POINT_LIGHT_NUMBER);
    return true;
}

void LightObject::setColor(const Color4F &color) {
//    for (auto &vertex : _bufferGLCube) {
//        vertex.colors = color;
//    }
//    _dirty = true;
}

void LightObject::setMaterial(const std::string &diffusePath, const std::string &specularPath, float shininess) {
    if (!diffusePath.empty()) {
        _diffuseTextureId = Loader::getInstance()->loadTexture(diffusePath).textureId;
    }

    if (!specularPath.empty()) {
        _specularTextureId = Loader::getInstance()->loadTexture(specularPath).textureId;
    }

    _shininess = shininess;
    _materialType = MaterialType::TEXTURE;

    _glProgram->use();
    _glProgram->setFloat("textureMaterial.shininess", _shininess);
    _glProgram->setInt("materialType", _materialType);
}

void LightObject::setMaterial(const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor, const glm::vec3 &specularColor, float shininess) {
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

void LightObject::addDirectionLight(const DirectionLight *directionLight) {
    _directionLight = directionLight;

    _glProgram->use();
    _glProgram->setVec3("dirLight.direction", _directionLight->getDirection());
    _glProgram->setVec3("dirLight.ambient", _directionLight->getAmbient());
    _glProgram->setVec3("dirLight.diffuse", _directionLight->getDiffuse());
    _glProgram->setVec3("dirLight.specular", _directionLight->getSpecular());
}

void LightObject::addPointLight(const PointLight *pointLight) {
    if (_capacityPointLight < POINT_LIGHT_NUMBER) {
        _pointLight[_capacityPointLight] = pointLight;
        _capacityPointLight++;
        _pointLightDirty = true;

    } else {
        printf("No more point light.");
    }

}

void LightObject::addSpotLight(const SpotLight *spotLight) {
    _spotLight = spotLight;
    _spotLightDirty = true;
}

void LightObject::setPosition(const glm::vec3 &position) {
    _position = glm::mat4();
    _position = glm::translate(_position, position);
}

void LightObject::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    _glProgram->use();

    if (_diffuseTextureId) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _diffuseTextureId);
        _glProgram->setInt("textureMaterial.diffuse", 0);
    }
    if (_specularTextureId) {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, _specularTextureId);
        _glProgram->setInt("textureMaterial.specular", 1);
    }

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
}
