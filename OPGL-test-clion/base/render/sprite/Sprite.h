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
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

private:
    Texture         _texture;

    bool            _dirty;
    unsigned int    _vao;
    unsigned int    _vbo;
    unsigned int    _ebo;
    Shader          *_glProgram;

    V3F_C4F_T2F     _bufferGlSprite[4] = {
        // 位置                  // 颜色                    // 纹理坐标
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,     // 右上
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,     // 右下
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 0.0f,     // 左下
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,   0.0f, 1.0f      // 左上
    };

    unsigned int indices[6] = {
            0, 1, 3,    // 第一个三角形
            1, 2, 3     // 第二个三角形
    };

};


#endif //OPGL_TEST_CLION_SPRITE_H
