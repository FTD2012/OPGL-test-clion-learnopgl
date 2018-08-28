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
#include <GLFW/glfw3.h>
#include <loader/Model.h>

MainScene::MainScene() {
    init();
}

MainScene::~MainScene() {

}

void MainScene::init() {
    // line
    int worldWidth = 200;   // x
    int worldHeight = 200;  // y
    int worldDepth = 200;   // z
    auto *lineRender = new Line();
    lineRender->drawLine({0.0f,  0.0f, 0.0f}, {static_cast<float>(worldWidth), 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    lineRender->drawLine({-1.0f * static_cast<float>(worldWidth),  0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    lineRender->drawLine({0.0f,  0.0f, 0.0f}, {0.0f, static_cast<float>(worldHeight), 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
    lineRender->drawLine({0.0f, -1.0f * static_cast<float>(worldHeight), 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

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
//    // xy平面垂直于x轴的线
//    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
//        if (i != 0.0f) {
//            lineRender->drawLine({static_cast<float>(i), -1 * static_cast<float>(worldHeight), 0.0f}, {static_cast<float>(i), static_cast<float>(worldHeight), 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }
//    // xy平面垂直于y轴的线
//    for (int i = -1 * worldHeight; i <= worldHeight; i++) {
//        if (i != 0.0f) {
//            lineRender->drawLine({-1 * static_cast<float>(worldWidth), static_cast<float>(i), 0.0f}, {static_cast<float>(worldWidth), static_cast<float>(i), 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }
//    // yz平面垂直于y轴的线
//    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
//        if (i != 0.0f) {
//            lineRender->drawLine({0.0f, static_cast<float>(i), -1 * static_cast<float>(worldDepth)}, {0.0f, static_cast<float>(i), static_cast<float>(worldDepth)}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }
//    // yz平面垂直于z轴的线
//    for (int i = -1 * worldDepth; i <= worldDepth; i++) {
//        if (i != 0.0f) {
//            lineRender->drawLine({0.0f, -1 * static_cast<float>(worldWidth), static_cast<float>(i)}, {0.0f, static_cast<float>(worldWidth), static_cast<float>(i)}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }


    auto *directionLight = new DirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
    addChild(directionLight);

    auto *cube1 = new Cube(glm::vec3(-1.0f, 0.5f, -50.0f));
    cube1->setMaterial("../../texture/marble.jpg", "../../texture/marble.jpg");
    cube1->addDirectionLight(directionLight);
    auto *cube2 = new Cube(glm::vec3(2.0f, 0.5f, 0.0f));
    cube2->setMaterial("../../texture/marble.jpg", "../../texture/marble.jpg");
    cube2->addDirectionLight(directionLight);

    addChild(cube1);
    addChild(cube2);
    addChild(lineRender);

}

void MainScene::onDraw(const Camera &camera) {

    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);

    Scene::onDraw(cameraPos, view, projection);

}
