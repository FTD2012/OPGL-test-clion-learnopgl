//
// Created by lvjiaming on 2018/8/14.
//

#ifndef OPGL_TEST_CLION_CUBE_H
#define OPGL_TEST_CLION_CUBE_H

#include <string>

#include <Shader.h>
#include <camera/Camera.h>
#include <render/types/types.h>
#include <light/directionLight/DirectionLight.h>
#include <light/pointLight/PointLight.h>
#include <vector>

#define VERTICES_NUMBER (36)
#define POINT_LIGHT_NUMBER (4)
class PointLight;
class Cube {

public:

    explicit Cube(const glm::vec3 &position = glm::vec3(0.0f));
    ~Cube();
    void init();
    void setColor(const Color4F &color);

    /**
     * 使用纹理作为材质
     * @param diffusePath
     * @param specularPath
     * @param shininess
     */
    void setMaterial(const std::string &diffusePath, const std::string &specularPath, float shininess = 32.0f);
    void setMaterial(const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor, const glm::vec3 &specularColor, float shininess);
    void addDirectionLight(const DirectionLight &directionLight);
    void addPointLight(const PointLight &pointLight);
    void setPosition(const glm::vec3 &position);
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection);

private:

    /**
     * 材质
     */
    enum MaterialType {
        TEXTURE = 1,
        COLOR   = 2
    };
    MaterialType             _materialType;

    /**
     * 使用纹理作为材质
     */
    unsigned int             _diffuseTextureId;
    unsigned int             _specularTextureId;
    float                    _shininess;

    /**
     * 使用颜色作为材质
     */
    glm::vec3                _ambientColor;
    glm::vec3                _diffuseColor;
    glm::vec3                _specularColor;

    glm::mat4                _position;
    bool                     _dirty;
    unsigned int             _vao;
    unsigned int             _vbo;
    Shader                   *_glProgram;

    DirectionLight           _directionLight;

    size_t                   _capacityPointLight;
    std::vector<const PointLight*>  _pointLight;

    V3F_N3F_T2F_C4F _bufferGLCube[VERTICES_NUMBER] = {
            // 顶点位置             // 法线向量           // 纹理坐标          // 颜色
            // positions           // normals           // texture coords   // color
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,   0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,   1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,   1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,   0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,   0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,

             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 0.0f,         1.0f, 1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f,         1.0f, 1.0f, 1.0f, 1.0f
    };

};


#endif //OPGL_TEST_CLION_CUBE_H
