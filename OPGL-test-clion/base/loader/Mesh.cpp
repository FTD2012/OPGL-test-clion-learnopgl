//
// Created by lvjiaming on 2018/8/20.
//

#include <loader/Mesh.h>
#include <external/glad.h>

#include <Config.h>
#include <loader/Loader.h>
#include <Macro.h>
#include <GLFW/glfw3.h>

Mesh::Mesh(std::vector<MeshVertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures)
: _vertices(std::move(vertices))
, _indices(std::move(indices))
, _textures(std::move(textures))
, _isEnableVisibleNormal(false)
, _isEnableInstancing(false)
{
    init();

    std::string diffuse;
    std::string specular;
    std::string normal;
    for (auto &it : _textures) {
        if (it.textureType == TextureType::DIFFUSE) {
            diffuse = it.path;
        } else if (it.textureType == TextureType::SPECULAR) {
            specular = it.path;
        } else if (it.textureType == TextureType::NORMALS) {
            normal = it.path;
        }
    }

    setMaterial(diffuse, specular, normal, 32.0f);
    CHECK_GL_ERROR_DEBUG();

}

Mesh::~Mesh() {
}

bool Mesh::init() {
    if (!LightObject::init()) {
        return false;
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, vertices));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normals));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, tangent));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, bitangent));
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, texCoords));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);

    _glProgram = new Shader(mesh_vertexShaderSource, mesh_fragmentShaderSource, mesh_geometryShaderSource);
    _glProgram->use();
    _glProgram->setBool("enableInstancing", false);
    return true;
}

void Mesh::setMaterial(const std::string &diffusePath, const std::string &specularPath, const std::string &normalPath, float shininess) {
    LightObject::setMaterial(diffusePath, specularPath, shininess);

    if (!normalPath.empty()) {
        _normalTextureId = Loader::getInstance()->loadTexture(normalPath).textureId;
    }

}

void Mesh::enableInstancing(bool isEnable, size_t size) {
    if (_isEnableInstancing == isEnable) {
        return;
    }
    _isEnableInstancing = isEnable;
    _instancingSize = size;

    _glProgram->use();
    _glProgram->setBool("enableInstancing", isEnable);

}

void Mesh::enableVisibleNormal(bool isEnable) {
    if (_isEnableVisibleNormal == isEnable) {
        return;
    }
    _isEnableVisibleNormal = isEnable;

    if (isEnable) {
        _glNormalProgram = new Shader(mesh_vertexShaderSource, mesh_visible_normal_fragmentShaderSource, mesh_visible_normal_geometryShaderSource);
        ASSERT(_glNormalProgram, "Invalid program!");
    } else {
        delete _glNormalProgram;
    }
}

void Mesh::bindInstancingBuffer() {
    GLsizei vec4Size = sizeof(glm::vec4);

    glBindVertexArray(_vao);

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2*vec4Size));
    glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3*vec4Size));

    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);
    glEnableVertexAttribArray(7);
    glEnableVertexAttribArray(8);

    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
    glVertexAttribDivisor(7, 1);
    glVertexAttribDivisor(8, 1);

    glBindVertexArray(0);
}

void Mesh::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {
    LightObject::onDraw(viewPos, view, projection);

    if (_normalTextureId) {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, _normalTextureId);
        _glProgram->setInt("textureMaterial.normal", 2);
    }

    glBindVertexArray(_vao);
    if (_isEnableInstancing) {
        glDrawElementsInstanced(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0, _instancingSize);
    } else {
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);


}

void Mesh::onDrawNormal(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    _glNormalProgram->use();
    _glNormalProgram->setMat4("model", _position);
    _glNormalProgram->setMat4("view", view);
    _glNormalProgram->setMat4("projection", projection);
    _glNormalProgram->setVec3("viewPos", viewPos);
    _glNormalProgram->setFloat("time", (float)glfwGetTime());

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}