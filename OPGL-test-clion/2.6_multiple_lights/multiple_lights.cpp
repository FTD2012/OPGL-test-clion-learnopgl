//
// Created by invoker on 2018/07/23.
//

//#define STB_IMAGE_IMPLEMENTATION
#include <external/glad.h>
#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <unistd.h>

#include <Shader.h>
#include <Config.h>
#include <Config.h>
#include <Macro.h>
#include <camera/Camera.h>
#include <loader/Loader.h>
#include <render/line/Line.h>
#include <render/cube/Cube.h>
#include <light/directionLight/DirectionLight.h>
#include <light/pointLight/PointLight.h>
#include <light/spotLight/SpotLight.h>

/**
 * @property {int} FPS 刷新帧数
 */
int FPS = 60;

/**
 * @property {float} frameSecond 每帧间隔时间
 */
float frameSecond = 1.0f/FPS;

/**
 * @property {float} deltaTime 当前帧与上一帧的时间差
 * @property {float} lastFrame 上一帧的时间
 */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/**
 * @property {int} ScreenWidth  屏幕宽度(Pixel)
 * @property {int} ScreenHeight 屏幕高度(Pixel)
 */
const int ScreenWidth = 800;
const int ScreenHeight = 600;

/**
 * 默认光标位置
 * @property {float} lastCursorX
 * @property {float} lastCursorY
 * @property {bool} firstMouse 鼠标位置是否初始化
 */
float lastCursorX;
float lastCursorY;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 7.0f, 13.0f));

/**
 * 告诉OpenGL渲染窗口的尺寸(视口Viewport)
 * 当用户改变窗口大小时，视口也被对应调整
 * @param {GLFWwindow*} window
 * @param {int} width  窗口宽度
 * @param {int} height 窗口高度
 */
void frameBuffer_size_callback(GLFWwindow *window, int width, int height) {
    UNUSED_PARAM(window);
    glViewport(0, 0, width, height);
}

/**
 * 处理键盘输入
 * @param {GLFWwindow*} window
*/
void processInput(GLFWwindow *window) {
    // space
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
        // up
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    }
        // down
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    }
        // w
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.onMove(Camera::Direction::FORWARD, deltaTime);
    }
        // s
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.onMove(Camera::Direction::BACKWARD, deltaTime);
    }
        // a
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.onMove(Camera::Direction::LEFT, deltaTime);
    }
        // d
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.onMove(Camera::Direction::RIGHT, deltaTime);
    }
}

/**
 * 处理鼠标位置变化，改变摄像机方向
 * @param {GLFWWindow*} window
 * @param {int} xPos 鼠标X轴位置(相对于屏幕像素)
 * @param {int} yPos 鼠标Y轴位置(相对于屏幕像素)
 */
void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    UNUSED_PARAM(window);

    if (firstMouse) {
        lastCursorX = (float)xPos;
        lastCursorY = (float)yPos;
        firstMouse = false;
    }

    auto xOffset = (float)(xPos - lastCursorX);
    auto yOffset = (float)(lastCursorY - yPos);
    lastCursorX = (float)xPos;
    lastCursorY = (float)yPos;

    camera.onMouseMove(xOffset, yOffset);
}

/**
 * 处理滚轮滚动变化，改变摄像机视角范围
 * @param {GLFWWindow*} window
 * @param {double} xOffset
 * @param {double} yOffset
 */
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset) {
    UNUSED_PARAM(window);
    UNUSED_PARAM(xOffset);

    camera.onZoom((float)yOffset);
}

int main() {

    /*
     *  GLFW
     */


    /*
     * 初始化GLFW库
     */
    glfwInit();

    /*
     * 设置主版本号和次版本号，opengl版本号为3，3
     */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /*
     * 设置抗锯齿
     */
    glfwWindowHint(GLFW_SAMPLES, 16);

    /*
     * 告诉GLFW使用opengl的核心模式
     */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*
     * 仅在MAC系统上使用该语句
     */
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /*
     * 创建一个和OPENGL/OPENGL ES上下文绑定的窗口
     */
    GLFWwindow *window = glfwCreateWindow(ScreenWidth, ScreenHeight, "好好学习OPENGL", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /*
     * '''
     * This function makes the OpenGL or OpenGL ES context of the specified window
     * current on the calling thread.
     * '''
     * 讲指定的 '窗口的OpenGL/OpenGL ES的上下文' 绑定到当前处理的线程。
     */
    glfwMakeContextCurrent(window);

    /*
     * 注册当窗口大小改变时的回调
     */
    glfwSetFramebufferSizeCallback(window, frameBuffer_size_callback);

    /*
     * 注册鼠标移动的回调
     */
    glfwSetCursorPosCallback(window, mouse_callback);

    /*
     * 注册滚轮变化的回调
     */
    glfwSetScrollCallback(window, scroll_callback);

    /*
     * GLAD
     */

    /*
     * GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD.
     * 我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
     */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

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
    DirectionLight directionLight;

    // point light
    PointLight pointLight({1.2f, 5.0f, 2.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);
    PointLight pointLight1({2.3f, 2.3f, -4.0f}, {0.05f, 0.05f, 0.05f}, {0.8f, 0.8f, 0.8f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);

    // spot light
    SpotLight spotLight({0.0f,  0.0f,  -4.0f} , glm::cos(glm::radians(2.5f)), glm::cos(glm::radians(3.0f)), {0.0f, 5.0f, 4.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 1.0f, 0.09f, 0.032f);

    // cube
    Cube lightCube, cubeRender[10];

    cubeRender[0].setMaterial("../../texture/container2.png", "../../texture/container2_specular.png", 32.0f);
    cubeRender[0].addDirectionLight(directionLight);
    cubeRender[0].addPointLight(pointLight);
    cubeRender[0].addPointLight(pointLight1);
    cubeRender[0].addSpotLight(spotLight);
    cubeRender[0].setPosition(cubePositions[0]);

    cubeRender[1].setMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
    cubeRender[1].addDirectionLight(directionLight);
    cubeRender[1].addPointLight(pointLight);
    cubeRender[1].addPointLight(pointLight1);
    cubeRender[1].addSpotLight(spotLight);
    cubeRender[1].setPosition(cubePositions[1]);

    cubeRender[2].setMaterial(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 32.f);
    cubeRender[2].addDirectionLight(directionLight);
    cubeRender[2].addPointLight(pointLight);
    cubeRender[2].addPointLight(pointLight1);
    cubeRender[2].addSpotLight(spotLight);
    cubeRender[2].setPosition(cubePositions[2]);

    cubeRender[3].setMaterial("../../texture/container2.png", "../../texture/container2_specular.png", 32.0f);
    cubeRender[3].addDirectionLight(directionLight);
    cubeRender[3].addPointLight(pointLight);
    cubeRender[3].addPointLight(pointLight1);
    cubeRender[3].addSpotLight(spotLight);
    cubeRender[3].setPosition(cubePositions[3]);

    cubeRender[4].setMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 128.f);
    cubeRender[4].addDirectionLight(directionLight);
    cubeRender[4].addPointLight(pointLight);
    cubeRender[4].addPointLight(pointLight1);
    cubeRender[4].addSpotLight(spotLight);
    cubeRender[4].setPosition(cubePositions[4]);

    cubeRender[5].setMaterial(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 32.f);
    cubeRender[5].addDirectionLight(directionLight);
    cubeRender[5].addPointLight(pointLight);
    cubeRender[5].addPointLight(pointLight1);
    cubeRender[5].addSpotLight(spotLight);
    cubeRender[5].setPosition(cubePositions[5]);

    // line
    int worldWidth = 500;   // x
    int worldHeight = 500;  // y
    int worldDepth = 500;   // z
    Line lineRender;
    lineRender.drawLine({0.0f,  0.0f, 0.0f}, {static_cast<float>(worldWidth), 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    lineRender.drawLine({-1.0f * static_cast<float>(worldWidth),  0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    lineRender.drawLine({0.0f,  0.0f, 0.0f}, {0.0f, static_cast<float>(worldHeight), 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
    lineRender.drawLine({0.0f, -1.0f * static_cast<float>(worldHeight), 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    lineRender.drawLine({0.0f,  0.0f, 0.0f}, {0.0f, 0.0f, static_cast<float>(worldDepth)}, {0.0f, 0.0f, 1.0f, 1.0f});
    lineRender.drawLine({0.0f, 0.0f, -1.0f * static_cast<float>(worldDepth)}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    // xz平面垂直于x轴的线
    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
        if (i != 0.0f) {
            lineRender.drawLine({static_cast<float>(i), 0.0f, -1 * static_cast<float>(worldDepth)}, {static_cast<float>(i), 0.0f, static_cast<float>(worldDepth)}, {1.0f, 1.0f, 1.0f, 1.0f});
        }
    }
    // xz平面垂直于z轴的线
    for (int i = -1 * worldDepth; i <= worldDepth; i++) {
        if (i != 0.0f) {
            lineRender.drawLine({-1 * static_cast<float>(worldWidth), 0.0f, static_cast<float>(i)}, {static_cast<float>(worldWidth), 0.0f, static_cast<float>(i)}, {1.0f, 1.0f, 1.0f, 1.0f});
        }
    }
//    // xy平面垂直于x轴的线
//    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
//        if (i != 0.0f) {
//            lineRender.drawLine({static_cast<float>(i), -1 * static_cast<float>(worldHeight), 0.0f}, {static_cast<float>(i), static_cast<float>(worldHeight), 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }
//    // xy平面垂直于y轴的线
//    for (int i = -1 * worldHeight; i <= worldHeight; i++) {
//        if (i != 0.0f) {
//            lineRender.drawLine({-1 * static_cast<float>(worldWidth), static_cast<float>(i), 0.0f}, {static_cast<float>(worldWidth), static_cast<float>(i), 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }
//    // yz平面垂直于y轴的线
//    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
//        if (i != 0.0f) {
//            lineRender.drawLine({0.0f, static_cast<float>(i), -1 * static_cast<float>(worldDepth)}, {0.0f, static_cast<float>(i), static_cast<float>(worldDepth)}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }
//    // yz平面垂直于z轴的线
//    for (int i = -1 * worldDepth; i <= worldDepth; i++) {
//        if (i != 0.0f) {
//            lineRender.drawLine({0.0f, -1 * static_cast<float>(worldWidth), static_cast<float>(i)}, {0.0f, static_cast<float>(worldWidth), static_cast<float>(i)}, {1.0f, 1.0f, 1.0f, 1.0f});
//        }
//    }

    /**
     * 使用 线框模式(Wireframe Mode) 绘制
     * 配置OpenGl如何绘制图元
     * @param1: 将配置应用到三角形的正面和背面
     * @param2: 使用线来绘制
     */
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* 使用 填充模式 绘制 */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* 启用深度测试 */
    glEnable(GL_DEPTH_TEST);

    /* 开启抗锯齿 */
    glEnable(GL_MULTISAMPLE);

    /*
     * MainLoop
     */

    glm::mat4 view;                                         // 相对世界坐标系
    glm::mat4 projection;                                   // 相对于摄像机
    glm::vec3 cameraPos;                                    // 摄像机位置
    glm::vec3 lightPosition;
    glm::vec3 lightDir;
    auto radius        = (float)glm::sqrt(pow(pointLight.getPosition().x, 2) + pow(pointLight.getPosition().z, 2));
    auto rSpotLight    = (float)glm::sqrt(pow(spotLight.getPosition().y, 2) + pow(spotLight.getPosition().z, 2));


    /*
     * - glfwWindowShouldClose 函数在每帧开始时会检测GLFW是否要退出
     * - glfwPollEvents 函数检查有没有触发事件(键盘输入、鼠标移动)，此时可以更新窗口状态
     * - glfwSwapBuffers 函数会交换颜色缓冲区
     */
    while(!glfwWindowShouldClose(window)) {
        /**
         * frame time
         */
        auto currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastFrame;
        if (deltaTime < frameSecond) {
            usleep((unsigned int)((frameSecond-deltaTime)*10e3));
            continue;
        }
        lastFrame = currentTime;

        // TODO: ljm >>> add log
#ifdef SHOW_FPS
        std::cout << "currentTime: " << currentTime << std::endl;
        std::cout << "deltaTime: " << deltaTime << std::endl;
        std::cout << "lastFrame: " << lastFrame << std::endl;
        std::cout << "FPS: " << (int)(1 / deltaTime) << std::endl;
#endif


        /*
         * 处理用户输入
         */
        processInput(window);

        /*
         * 渲染
         */
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        cameraPos = camera.getPosition();
        view = camera.getViewMatrix();
        projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);
        lightPosition = glm::vec3(glm::cos(glfwGetTime()) * radius, pointLight.getPosition().y, glm::sin(glfwGetTime()) * radius);
        pointLight.setPosition(lightPosition);

        lightPosition = glm::vec3(spotLight.getPosition().x, glm::cos(glfwGetTime()) * rSpotLight, glm::sin(glfwGetTime()) * rSpotLight);
        lightDir = glm::vec3(0.0f, 5.0f, 0.0f) - lightPosition;
        spotLight.setPosition(lightPosition);
        spotLight.setDirection(lightDir);

        // draw line
        lineRender.onDrawLine(view, projection);

        /// draw object
        for (int i = 0; i < 6; i++) {
            cubeRender[i].onDraw(cameraPos, view, projection);
        }

        // draw light
        pointLight.onDraw(cameraPos, view, projection);
        pointLight1.onDraw(cameraPos, view, projection);
        spotLight.onDraw(cameraPos, view, projection);

        /*
         * 交换缓冲区
         */
        glfwSwapBuffers(window);

        /*
         * 检查触发时间
         */
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
