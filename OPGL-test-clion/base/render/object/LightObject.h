//
// Created by lvjiaming on 2018/8/21.
//

#ifndef OPGL_TEST_CLION_LIGHTOBJECT_H
#define OPGL_TEST_CLION_LIGHTOBJECT_H

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

class LightObject: public Object {

public:
    explicit LightObject(const glm::vec3 &position = glm::vec3(0.0f));
    explicit LightObject(const std::string &diffusePath, const std::string &specularPath, float shininess = 32.0f, const glm::vec3 &position = glm::vec3(0.0f));

    ~LightObject() override;

    virtual bool init();
    void setColor(const Color4F &color);

    /**
     * 使用纹理作为材质
     * @param diffusePath
     * @param specularPath
     * @param shininess
     */
    void setMaterial(const std::string &diffusePath, const std::string &specularPath, float shininess = 32.0f);
    void setMaterial(const glm::vec3 &ambientColor, const glm::vec3 &diffuseColor, const glm::vec3 &specularColor, float shininess);
    void addDirectionLight(const DirectionLight *directionLight);
    void addPointLight(const PointLight *pointLight);
    void addSpotLight(const SpotLight *spotLight);
    void setPosition(const glm::vec3 &position);
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

protected:
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

    glm::mat4                _position;
    bool                     _dirty;
    unsigned int             _vao;
    unsigned int             _vbo;
    unsigned int             _ebo;
    Shader                   *_glProgram;

    const DirectionLight     *_directionLight;

    size_t                   _capacityPointLight;
    std::vector<const PointLight*>  _pointLight;
    bool                     _pointLightDirty;

    const SpotLight          *_spotLight;
    bool                     _spotLightDirty;

};


#endif //OPGL_TEST_CLION_LIGHTOBJECT_H
