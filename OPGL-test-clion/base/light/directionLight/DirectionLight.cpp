//
// Created by lvjiaming on 2018/8/15.
//

#include "DirectionLight.h"

const glm::vec3 DirectionLight::DIRECTION = glm::vec3(-0.2f, -1.0f, -0.3f);
const glm::vec3 DirectionLight::AMBIENT   = glm::vec3(0.25f,  0.25f, 0.25f);
const glm::vec3 DirectionLight::DIFFUSE   = glm::vec3(0.5f,   0.5f,  0.5f);
const glm::vec3 DirectionLight::SPECULAR  = glm::vec3(0.5f,   0.5f,  0.5f);

//const glm::vec3 DirectionLight::DIRECTION = glm::vec3(-1.2f, -1.0f, -2.0f);
//const glm::vec3 DirectionLight::AMBIENT   = glm::vec3(1.0f, 1.0f, 1.0f);
//const glm::vec3 DirectionLight::DIFFUSE   = glm::vec3(1.0f, 1.0f, 1.0f);
//const glm::vec3 DirectionLight::SPECULAR  = glm::vec3(1.0f, 1.0f, 1.0f);

DirectionLight::DirectionLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
: _direction(direction)
, _ambient(ambient)
, _diffuse(diffuse)
, _specular(specular)
{

}

void DirectionLight::setDirection(const glm::vec3 &direction) {
    _direction = direction;
}

void DirectionLight::setAmbient(const glm::vec3 &ambient) {
    _ambient = ambient;
}

void DirectionLight::setDiffuse(const glm::vec3 &diffuse) {
    _diffuse = diffuse;
}

void DirectionLight::setSpecular(const glm::vec3 &specular) {
    _specular = specular;
}

const glm::vec3 &DirectionLight::getDirection() const{
    return _direction;
}

const glm::vec3 &DirectionLight::getAmbient() const{
    return _ambient;
}

const glm::vec3 &DirectionLight::getDiffuse() const{
    return _diffuse;
}

const glm::vec3 &DirectionLight::getSpecular() const{
    return _specular;
}