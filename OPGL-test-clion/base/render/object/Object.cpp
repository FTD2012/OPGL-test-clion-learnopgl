//
// Created by lvjiaming on 2018/8/17.
//

#include <render/object/Object.h>

Object::Object() {

}

Object::~Object() {
    for (auto &it : _children) {
        delete it;
    }
}

void Object::addChild(Object *object) {
    _children.push_back(object);
}

void Object::setPosition(const glm::vec3 &position) {
    _position = glm::mat4();
    _position = glm::translate(_position, position);
}

void Object::setBoarder(const glm::vec3 &color) {

}

void Object::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

}


