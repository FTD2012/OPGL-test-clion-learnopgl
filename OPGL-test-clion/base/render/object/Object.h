//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_OBJECT_H
#define OPGL_TEST_CLION_OBJECT_H

#include <vector>

#include <external/glm/vec3.hpp>

#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>

class Object {
public:
    Object();
    virtual ~Object();

    virtual void addChild(Object *object);
    virtual void setPosition(const glm::vec3 &position);
    virtual void setBoarder(const glm::vec3 &color);
    virtual void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection);

protected:

    std::vector<Object*> _children;
    glm::mat4            _position;

};


#endif //OPGL_TEST_CLION_OBJECT_H
