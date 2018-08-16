//
// Created by invoker on 2018/8/16.
//

#ifndef OPGL_TEST_CLION_SPOTLIGHT_H
#define OPGL_TEST_CLION_SPOTLIGHT_H

#include <light/pointLight/PointLight.h>

class SpotLight: public PointLight {
public:
    explicit SpotLight(const glm::vec3 &direction   = SpotLight::DIRECTION,
                       float            cutOff      = SpotLight::CUT_OFF,
                       float            outerCutOff = SpotLight::OUTER_CUT_OFF,
                       const glm::vec3 &position    = PointLight::POSITION,
                       const glm::vec3 &ambient     = PointLight::AMBIENT,
                       const glm::vec3 &diffuse     = PointLight::DIFFUSE,
                       const glm::vec3 &specular    = PointLight::SPECULAR,
                       float            constant    = PointLight::CONSTANT,
                       float            linear      = PointLight::LINEAR,
                       float            quadratic   = PointLight::QUADRATIC);

    void setDirection(const glm::vec3 &direction);

    const glm::vec3 &getDirection() const;
    float getCutOff() const;
    float getOuterCutOff() const;

private:

    glm::vec3 _direction;
    float     _cutOff;
    float     _outerCutOff;

protected:

    static const glm::vec3 DIRECTION;
    static const float     CUT_OFF;
    static const float     OUTER_CUT_OFF;

};


#endif //OPGL_TEST_CLION_SPOTLIGHT_H
