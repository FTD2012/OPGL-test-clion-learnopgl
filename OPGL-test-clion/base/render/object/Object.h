//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_OBJECT_H
#define OPGL_TEST_CLION_OBJECT_H

#include <vector>

#include <external/glm/detail/type_mat.hpp>
#include <external/glm/vec3.hpp>


class Object {
public:
    Object();
    virtual ~Object();

    virtual void addChild(Object *object);
    virtual void setBoarder(const glm::vec3 &color);
    virtual void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection);

protected:

    std::vector<Object*> _children;

};


#endif //OPGL_TEST_CLION_OBJECT_H
