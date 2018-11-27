//
// Created by lvjiaming on 2018/8/17.
//

#include <render/line/Line.h>
#include <Config.h>
#include "MainScene.h"
#include <render/line/Line.h>
#include <render/cube/Cube.h>
#include <light/directionLight/DirectionLight.h>
#include <light/pointLight/PointLight.h>
#include <light/spotLight/SpotLight.h>
#include <render/sprite/Sprite.h>
#include <GLFW/glfw3.h>
#include <loader/Model.h>
#include <Constant.h>
#include <Macro.h>

#include <algorithm>

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

//    auto *directionLight = new DirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
//    addChild(directionLight);
//
//    auto *cube1 = new Cube(glm::vec3(0.0f, 0.5f, -2.0f));
//    cube1->setColor({0.0f, 1.0f, 0.0f, 1.0f});
//    cube1->setMaterial("../../texture/marble.jpg", "../../texture/marble.jpg");
//    cube1->addDirectionLight(directionLight);
//    addChild(cube1);
//
//    auto *cube2 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
//    cube2->setColor({0.0f, 1.0f, 0.0f, 1.0f});
//    cube2->setMaterial("../../texture/marble.jpg", "../../texture/marble.jpg");
//    cube2->addDirectionLight(directionLight);
//    addChild(cube2);

    // direction light
    auto *directionLight = new DirectionLight();
    auto *pointLight = new PointLight({1.2f, 5.0f, 2.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);
    auto *nanoSuitModel = new Model("../../texture/nanosuit/nanosuit.obj");
    nanoSuitModel->addDirectionLight(directionLight);
    nanoSuitModel->addPointLight(pointLight);
    addChild(nanoSuitModel);
    addChild(pointLight);

    enableCubeMap(true);
}

void MainScene::onDraw(const Camera &camera) {
    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);
    Scene::onDraw(cameraPos, view, projection);
}

