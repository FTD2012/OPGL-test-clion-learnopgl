//
// Created by lvjiaming on 2018/8/17.
//

#include <algorithm>

#include <render/point/Point.h>
#include <Config.h>
#include "MainScene.h"

// Magic. Don't Move.
//#include <GLFW/glfw3.h>

extern Camera camera;

bool sortByDistance(const glm::vec3 &pos1, const glm::vec3 &pos2) {
    return (camera.getPosition().z - pos1.z) > (camera.getPosition().z - pos2.z);
}

MainScene::MainScene() {
    init();
}

MainScene::~MainScene() {
    
}

void MainScene::init() {
    this->drawWorld();

    auto point = new Point();
    point->drawPoint({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
    point->drawPoint({1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    point->drawPoint({-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f});
    point->drawPoint({0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
    point->drawPoint({0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f});

    this->addChild(point);

}

void MainScene::onDraw(const Camera &camera) {
    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);
    Scene::onDraw(cameraPos, view, projection);
}

