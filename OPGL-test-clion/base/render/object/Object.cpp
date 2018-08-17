//
// Created by lvjiaming on 2018/8/17.
//

#include <render/object/Object.h>

Object::Object() {
//    _children.resize(20);
}

Object::~Object() {
//    _children.resize(0);
}


void Object::addChild(Object *object) {
    _children.push_back(object);
}

void Object::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

}


