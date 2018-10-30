//
// Created by invoker on 2018/07/23.
//

#define STB_IMAGE_IMPLEMENTATION
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
#include <Macro.h>
#include <camera/Camera.h>
#include <loader/Loader.h>
#include "MainScene.h"

/**
 * 默认光标位置
 * @property {float} lastCursorX
 * @property {float} lastCursorY
 * @property {bool} firstMouse 鼠标位置是否初始化
 */
float lastCursorX;
float lastCursorY;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 2.0f, 6.0f));

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
     * 隐藏鼠标
     */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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


    auto *mainScene = new MainScene();

    /**
     * 使用 线框模式(Wireframe Mode) 绘制
     * 配置OpenGl如何绘制图元
     * @param1: 将配置应用到三角形的正面和背面
     * @param2: 使用线来绘制
     */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* 使用 填充模式 绘制 */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* 启用深度测试 */
    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_ALWAYS);

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
        if ((int)(1 / deltaTime) < 59) {
            std::cout << "currentTime: " << currentTime << std::endl;
            std::cout << "deltaTime: " << deltaTime << std::endl;
            std::cout << "lastFrame: " << lastFrame << std::endl;
            std::cout << "FPS: " << (int) (1 / deltaTime) << std::endl;
        }
#endif


        /*
         * 处理用户输入
         */
        processInput(window);

        /*
         * 渲染
         */
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        // render
        mainScene->onDraw(camera);

        /*
         * 交换缓冲区
         */
        glfwSwapBuffers(window);

        /*
         * 检查触发时间
         */
        glfwPollEvents();
    }

    delete mainScene;
    glfwTerminate();
    return EXIT_SUCCESS;
}
