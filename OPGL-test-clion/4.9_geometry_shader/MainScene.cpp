//
// Created by lvjiaming on 2018/8/17.
//

#include <algorithm>

#include <render/point/Point.h>
#include <Config.h>
#include <loader/Model.h>
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

    auto *directionLight = new DirectionLight();
    auto *pointLight = new PointLight({1.2f, 15.0f, 3.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);
    auto *spotLight = new SpotLight();
    auto *nanoSuitModel = new Model("../../texture/nanosuit/nanosuit.obj");
    nanoSuitModel->addDirectionLight(directionLight);
    nanoSuitModel->addPointLight(pointLight);
    addChild(nanoSuitModel);
    addChild(pointLight);

//    enableCubeMap(true);
}

void MainScene::onDraw(const Camera &camera) {
    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);
    Scene::onDraw(cameraPos, view, projection);
}

