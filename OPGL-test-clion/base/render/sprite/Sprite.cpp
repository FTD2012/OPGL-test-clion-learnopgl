//
// Created by lvjiaming on 2018/10/9.
//

#include <Config.h>
#include <loader/Loader.h>
#include "Sprite.h"

Sprite::Sprite() {
    init();
}

Sprite::Sprite(const std::string &path):Sprite() {
    setTexture(path);
}

Sprite::~Sprite() {

}

void Sprite::init() {
    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4F_T2F)*4, _bufferGlSprite, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F_T2F), (void *)offsetof(V3F_C4F_T2F, vertices));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F_T2F), (void *)offsetof(V3F_C4F_T2F, colors));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F_T2F), (void *)offsetof(V3F_C4F_T2F, texCoords));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _glProgram = new Shader(texture_vertexShaderSource, texture_fragmentShaderSource);
    setPosition({0.0f, 0.0f, 0.0f});
}

void Sprite::setTexture(const std::string &path) {
    _texture = Loader::getInstance()->loadTexture(path);
    _glProgram->use();
    _glProgram->setInt("texture1", 0);
}

void Sprite::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    if (_texture.textureId) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture.textureId);

        _glProgram->use();
        _glProgram->setMat4("model", _position);
        _glProgram->setMat4("view", view);
        _glProgram->setMat4("projection", projection);
        _glProgram->setVec3("viewPos", viewPos);

        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);

}