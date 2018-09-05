//
// Created by lvjiaming on 2018/8/14.
//

#ifndef OPGL_TEST_CLION_CUBE_H
#define OPGL_TEST_CLION_CUBE_H

#include <string>
#include <vector>

#include <Shader.h>
#include <camera/Camera.h>
#include <render/types/types.h>
#include <light/directionLight/DirectionLight.h>
#include <light/pointLight/PointLight.h>
#include <light/spotLight/SpotLight.h>
#include <render/object/Object.h>

#define VERTICES_NUMBER (36)
#define POINT_LIGHT_NUMBER (4)
class PointLight;
class SpotLight;
class Cube :public Object {

public:

    explicit Cube(const glm::vec3 &position = glm::vec3(0.0f));
    ~Cube() override;
    void init();
    void setColor(const Color4F &color);

    /**
     * 使用纹理作为材质
     * @param diffusePath
     * @param specularPath
     * @param shininess
     */
    void setMaterial(const std::string &diffusePath = "", const std::string &specularPath = "", float shininess = 32.0f);
    void setMaterial(const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor, const glm::vec3 &specularColor, float shininess);
    void addDirectionLight(const DirectionLight *directionLight);
    void addPointLight(const PointLight *pointLight);
    void addSpotLight(const SpotLight *spotLight);
    void setPosition(const glm::vec3 &position);
    void setBoarder(const glm::vec3 &color) override;
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

private:
    /**
     * 材质
     * material
     * @link http://devernay.free.fr/cours/opengl/materials.html
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

    /*
     * 描边
     */
    bool                     _enableBorder;
    glm::vec3                _borderColor;
    Shader                   *_borderGlProgram;

    glm::mat4                _position;
    bool                     _dirty;
    unsigned int             _vao;
    unsigned int             _vbo;
    Shader                   *_glProgram;

    const DirectionLight     *_directionLight;
    bool                     _directionLightDirty;

    size_t                   _capacityPointLight;
    std::vector<const PointLight*>  _pointLight;
    bool                     _pointLightDirty;

    const SpotLight          *_spotLight;
    bool                     _spotLightDirty;

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
