//
// Created by lvjiaming on 2018/8/16.
//

#include "PointLight.h"

const glm::vec3 PointLight::POSITION = glm::vec3(10.0f, 10.0f, -10.0f);
const glm::vec3 PointLight::AMBIENT = glm::vec3(0.05f, 0.05f, 0.05f);
const glm::vec3 PointLight::DIFFUSE = glm::vec3(0.8f, 0.8f, 0.8f);
const glm::vec3 PointLight::SPECULAR = glm::vec3(1.0f, 1.0f, 1.0f);

const float PointLight::CONSTANT = 1.0f;
const float PointLight::LINEAR = 0.09f;
const float PointLight::QUADRATIC = 0.032f;

PointLight::PointLight(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float constant, float linear, float quadratic)
: _position(position)
, _ambient(ambient)
, _diffuse(diffuse)
, _specular(specular)
, _constant(constant)
, _linear(linear)
, _quadratic(quadratic)
{
    _cube = new Cube(position);
    _cube->setColor({1.0f, 1.0f, 1.0f, 1.0f});
}

void PointLight::setPosition(const glm::vec3 &position) {
    _position = position;
    _cube->setPosition(_position);
}

void PointLight::setAttenuation(float constant, float linear, float quadratic) {
    _constant = constant;
    _linear = linear;
    _quadratic = quadratic;
}

const glm::vec3 &PointLight::getPosition() const {
    return _position;
}

const glm::vec3 &PointLight::getAmbient() const {
    return _ambient;
}

const glm::vec3 &PointLight::getDiffuse() const {
    return _diffuse;
}

const glm::vec3 &PointLight::getSpecular() const {
    return _specular;
}

float PointLight::getConstant() const {
    return _constant;
}

float PointLight::getLinear() const {
    return _linear;
}

float PointLight::getQuadratic() const {
    return _quadratic;
}

void PointLight::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {
    _cube->onDraw(viewPos, view, projection);
}
