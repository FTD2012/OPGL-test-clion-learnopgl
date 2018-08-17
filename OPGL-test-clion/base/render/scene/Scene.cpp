//
// Created by lvjiaming on 2018/8/17.
//

#include <render/scene/Scene.h>

Scene::Scene() {
}

Scene::~Scene() {
}


void Scene::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    for (auto &it : _children) {
        it->onDraw(viewPos, view, projection);
    }


}