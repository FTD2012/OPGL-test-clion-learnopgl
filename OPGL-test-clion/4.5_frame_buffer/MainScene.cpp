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

    auto *directionLight = new DirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
    addChild(directionLight);

    auto *cube1 = new Cube(glm::vec3(0.0f, 0.5f, -2.0f));
    cube1->setColor({0.0f, 1.0f, 0.0f, 1.0f});
    cube1->setMaterial("../../texture/marble.jpg", "../../texture/marble.jpg");
    cube1->addDirectionLight(directionLight);
    addChild(cube1);

    auto *cube2 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
    cube2->setMaterial("../../texture/marble.jpg", "../../texture/marble.jpg");
    cube2->addDirectionLight(directionLight);
    addChild(cube2);

    std::sort(vegetation.begin(), vegetation.end(), sortByDistance);
    std::for_each(vegetation.begin(), vegetation.end(), [=](glm::vec3 &pos) {
        auto *grass = new Sprite("../../texture/window.png");
        grass->setPosition(pos);
        addChild(grass);
    });

    setFilter(Filter::KERNEL_EDGE_DETECTION);
}

void MainScene::onDraw(const Camera &camera) {
    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);
    Scene::onDraw(cameraPos, view, projection);
}

