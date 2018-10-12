//
// Created by lvjiaming on 2018/10/9.
//

#ifndef OPGL_TEST_CLION_SPRITE_H
#define OPGL_TEST_CLION_SPRITE_H

#include <render/object/Object.h>
#include <camera/Camera.h>
#include <string>
#include <Shader.h>
#include <render/types/types.h>

class Sprite: public Object {

public:
    Sprite();
    explicit Sprite(const std::string &path);
    ~Sprite() override;
    void init();
    void setTexture(const std::string &path);
    void setTexture(int textureId);
    void onDraw(const glm::vec3 &viewPos = glm::vec3(), const glm::mat4 &view = glm::mat4(), const glm::mat4 &projection = glm::mat4()) override;

private:
    Texture         _texture;

    bool            _dirty;
    unsigned int    _vao;
    unsigned int    _vbo;
    unsigned int    _ebo;
    Shader          *_glProgram;

    V3F_C4F_T2F     _bufferGlSprite[4] = {
        // 位置                  // 颜色                    // 纹理坐标
         1.0f,  1.0f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,     // 右上
         1.0f, -1.0f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,     // 右下
        -1.0f, -1.0f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // 左下
        -1.0f,  1.0f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,   0.0f, 1.0f      // 左上
    };

    unsigned int indices[6] = {
            0, 1, 3,    // 第一个三角形
            1, 2, 3     // 第二个三角形
    };

};


#endif //OPGL_TEST_CLION_SPRITE_H
