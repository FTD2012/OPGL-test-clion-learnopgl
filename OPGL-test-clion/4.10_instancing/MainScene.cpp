//
// Created by lvjiaming on 2018/8/17.
//

#include <algorithm>
#include <random>

#include <render/point/Point.h>
#include <Config.h>
#include <loader/Model.h>
#include "MainScene.h"

// Magic. Don't Move.
#include <GLFW/glfw3.h>

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

    size_t amount = 10;
    std::vector<glm::mat4> instancingMatrix;
    instancingMatrix.resize(0);

    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type > dist(1, amount*10);
    rng.seed(std::random_device()());

    for (int i = 0; i < amount; i++) {
//        auto *directionLight = new DirectionLight();
//        auto *pointLight = new PointLight({1.2f, 15.0f, dist(rng)}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);
//        auto *spotLight = new SpotLight();
//        auto *nanoSuitModel = new Model("../../texture/nanosuit/nanosuit.obj");
////        nanoSuitModel->addDirectionLight(directionLight);
////        nanoSuitModel->addPointLight(pointLight);
//        nanoSuitModel->setPosition({1.0f, 1.0f, dist(rng)});
//        addChild(nanoSuitModel);
////        addChild(pointLight);
        instancingMatrix.push_back(glm::translate(glm::mat4(), {0.0f, 1.0f, dist(rng)}));
    }

    auto *directionLight = new DirectionLight();
    auto *pointLight = new PointLight({1.2f, 15.0f, 3.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);
    auto *spotLight = new SpotLight();
    auto *nanoSuitModel = new Model("../../texture/nanosuit/nanosuit.obj");
//    nanoSuitModel->addDirectionLight(directionLight);
//    nanoSuitModel->addPointLight(pointLight);
//    nanoSuitModel->enableVisibleNormal(true);
    nanoSuitModel->enableInstancing(true, instancingMatrix);
    addChild(nanoSuitModel);
//    addChild(pointLight);


    enableCubeMap(true);
}

void MainScene::onDraw(const Camera &camera) {
    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);
    Scene::onDraw(cameraPos, view, projection);

}

