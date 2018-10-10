//
// Created by lvjiaming on 2018/8/16.
//

#ifndef OPGL_TEST_CLION_POINTLIGHT_H
#define OPGL_TEST_CLION_POINTLIGHT_H

#include <external/glm/vec3.hpp>
#include <external/glm/detail/type_mat.hpp>
#include <external/glad.h>
#include <render/object/Object.h>

class Cube;
class PointLight: public Object {

public:

    explicit  PointLight(const glm::vec3 &position  = PointLight::POSITION,
                         const glm::vec3 &ambient   = PointLight::AMBIENT,
                         const glm::vec3 &diffuse   = PointLight::DIFFUSE,
                         const glm::vec3 &specular  = PointLight::SPECULAR,
                         float            constant  = PointLight::CONSTANT,
                         float            linear    = PointLight::LINEAR,
                         float            quadratic = PointLight::QUADRATIC);

    void setAttenuation(float constant, float linear, float quadratic);

    const glm::vec3 &getPosition() const;
    const glm::vec3 &getAmbient() const;
    const glm::vec3 &getDiffuse() const;
    const glm::vec3 &getSpecular() const;
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;

    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;


protected:
    /**
     * 点光源光照强度衰减(Attenuation)公式
     *               1.0
     * Fatt = --------------------
     *         Kc + Kl*d + Kq*d^2
     */

    glm::vec3 _position;
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

    float     _constant;
    float     _linear;
    float     _quadratic;

    // draw
    Cube      *_cube;

protected:

    static const glm::vec3 POSITION;
    static const glm::vec3 AMBIENT;
    static const glm::vec3 DIFFUSE;
    static const glm::vec3 SPECULAR;
    static const float     CONSTANT;
    static const float     LINEAR;
    static const float     QUADRATIC;

};


#endif //OPGL_TEST_CLION_POINTLIGHT_H
