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

MainScene::MainScene() {
    init();
}

MainScene::~MainScene() {

}

void MainScene::init() {
    // line
    auto worldWidth = 500;   // x
    auto worldHeight = 500;  // y
    auto worldDepth = 500;   // z
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

    addChild(lineRender);

    // 10个立方体的位置
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  5.0f,  0.0f),
            glm::vec3( 0.0f,  5.0f,  8.0f),
            glm::vec3(-1.5f, 3.2f, -2.5f),
            glm::vec3(-3.8f, 3.0f, -12.3f),
            glm::vec3( 2.4f,  5.4f, -3.5f),
            glm::vec3(-1.7f,  8.0f, -7.5f),
            glm::vec3( 1.3f, 3.0f, -2.5f),
            glm::vec3( 1.5f,  7.0f, -2.5f),
            glm::vec3( 1.5f,  5.2f, -1.5f),
            glm::vec3(-1.3f,  6.0f, -1.5f)
    };

    // direction light
    auto *directionLight = new DirectionLight();

    // point light
    auto *pointLight = new PointLight({1.2f, 5.0f, 2.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);
    auto *pointLight1 = new PointLight({2.3f, 2.3f, -4.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);

    // spot light
    auto *spotLight = new SpotLight({0.0f,  0.0f,  -4.0f} , glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)), {0.0f, 5.0f, 4.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);

    // cube
    auto *lightCube = new Cube(), *cubeRender = new Cube[10]();

    addChild(directionLight);
    addChild(&cubeRender[0]);
    addChild(&cubeRender[1]);
    addChild(&cubeRender[2]);
    addChild(&cubeRender[3]);
    addChild(&cubeRender[4]);
    addChild(&cubeRender[5]);
    addChild(&cubeRender[6]);
    addChild(&cubeRender[7]);
    addChild(&cubeRender[8]);
    addChild(&cubeRender[9]);
    addChild(pointLight);
    addChild(pointLight1);
    addChild(spotLight);
    addChild(lightCube);

    for (size_t i = 0; i < 10; i++) {
        cubeRender[i].addDirectionLight(directionLight);
        cubeRender[i].addPointLight(pointLight);
        cubeRender[i].addPointLight(pointLight1);
        cubeRender[i].addSpotLight(spotLight);
        cubeRender[i].setPosition(cubePositions[i]);
    }

    cubeRender[0].setMaterial("../../texture/container2.png", "../../texture/container2_specular.png", 32.0f);
    cubeRender[1].setMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
    cubeRender[2].setMaterial(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 32.f);
    cubeRender[3].setMaterial("../../texture/container2.png", "../../texture/container2_specular.png", 32.0f);
    cubeRender[4].setMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 128.f);
    cubeRender[5].setMaterial(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 32.f);

}

void MainScene::onDraw(const Camera &camera) {

    glm::vec3 cameraPos = camera.getPosition();
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);

    Scene::onDraw(cameraPos, view, projection);

}
