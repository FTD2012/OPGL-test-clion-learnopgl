//
// Created by invoker on 2018/8/16.
//

#include <light/spotLight/SpotLight.h>
#include <external/glm/glm.hpp>

const glm::vec3 SpotLight::DIRECTION = glm::vec3(1.0f);
const float     SpotLight::CUT_OFF = glm::cos(glm::radians(12.5f));
const float     SpotLight::OUTER_CUT_OFF = glm::cos(glm::radians(17.5f));


SpotLight::SpotLight(const glm::vec3 &direction, const float cutOff, const float outerCutOff, const glm::vec3 &position,
                     const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float constant,
                     float linear, float quadratic)
: _direction(direction)
, _cutOff(cutOff)
, _outerCutOff(outerCutOff)
, PointLight(position, ambient, diffuse, specular, constant, linear, quadratic)
{

}

void SpotLight::setDirection(const glm::vec3 &direction) {
    _direction = direction;
}

const glm::vec3 &SpotLight::getDirection() const {
    return _direction;
}

float SpotLight::getCutOff() const {
    return _cutOff;
}

float SpotLight::getOuterCutOff() const {
    return _outerCutOff;
}