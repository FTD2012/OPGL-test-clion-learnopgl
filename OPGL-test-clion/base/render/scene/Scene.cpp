//
// Created by lvjiaming on 2018/8/17.
//

#include <render/scene/Scene.h>
#include <render/line/Line.h>

Scene::Scene() {
}

Scene::~Scene() {

}


void Scene::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    for (auto &it : _children) {
        it->onDraw(viewPos, view, projection);
    }

}

void Scene::drawWorld() {
    // line
    int worldWidth = 200;   // x
    int worldHeight = 200;  // y
    int worldDepth = 200;   // z
    auto *lineRender = new Line();
    lineRender->drawLine({0.0f,  0.0f, 0.0f}, {static_cast<float>(worldWidth), 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    lineRender->drawLine({-1.0f * static_cast<float>(worldWidth),  0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    // lineRender->drawLine({0.0f,  0.0f, 0.0f}, {0.0f, static_cast<float>(worldHeight), 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
    // lineRender->drawLine({0.0f, -1.0f * static_cast<float>(worldHeight), 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    lineRender->drawLine({0.0f,  0.0f, 0.0f}, {0.0f, 0.0f, static_cast<float>(worldDepth)}, {0.0f, 0.0f, 1.0f, 1.0f});
    lineRender->drawLine({0.0f, 0.0f, -1.0f * static_cast<float>(worldDepth)}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    // xz平面垂直于x轴的线
    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
        if (i != 0.0f) {
            lineRender->drawLine({static_cast<float>(i), 0.0f, -1 * static_cast<float>(worldDepth)}, {static_cast<float>(i), 0.0f, static_cast<float>(worldDepth)}, {1.0f, 1.0f, 1.0f, 1.0f});
        }
    }
    // xz平面垂直于z轴的线
    for (int i = -1 * worldDepth; i <= worldDepth; i++) {
        if (i != 0.0f) {
            lineRender->drawLine({-1 * static_cast<float>(worldWidth), 0.0f, static_cast<float>(i)}, {static_cast<float>(worldWidth), 0.0f, static_cast<float>(i)}, {1.0f, 1.0f, 1.0f, 1.0f});
        }
    }
    addChild(lineRender);
}