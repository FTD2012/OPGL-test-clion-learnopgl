//
// Created by lvjiaming on 2018/8/15.
//

#ifndef OPGL_TEST_CLION_DIRECTIONLIGHT_H
#define OPGL_TEST_CLION_DIRECTIONLIGHT_H


#include <external/glm/vec3.hpp>

class DirectionLight {
public:

    explicit DirectionLight(const glm::vec3 &direction = DirectionLight::DIRECTION,
                            const glm::vec3 &ambient   = DirectionLight::AMBIENT,
                            const glm::vec3 &diffuse   = DirectionLight::DIFFUSE,
                            const glm::vec3 &specular  = DirectionLight::SPECULAR);

    void setDirection(const glm::vec3 &direction);
    void setAmbient(const glm::vec3 &ambient);
    void setDiffuse(const glm::vec3 &diffuse);
    void setSpecular(const glm::vec3 &specular);

    const glm::vec3 &getDirection();
    const glm::vec3 &getAmbient();
    const glm::vec3 &getDiffuse();
    const glm::vec3 &getSpecular();

private:

    glm::vec3 _direction;
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;

private:

    static const glm::vec3 DIRECTION;
    static const glm::vec3 AMBIENT;
    static const glm::vec3 DIFFUSE;
    static const glm::vec3 SPECULAR;

};


#endif //OPGL_TEST_CLION_DIRECTIONLIGHT_H
