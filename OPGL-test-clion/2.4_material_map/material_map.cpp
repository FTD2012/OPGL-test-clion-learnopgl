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
#include <Macro.h>
#include <camera/Camera.h>
#include <loader/Loader.h>

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

Camera camera;

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

    // Shader
    Shader shaderProgram(material_map_vertexShaderSource, material_map_fragmentShaderSource);
    Shader lightShaderProgram(color_vertexShaderSource, material_light_fragmentShaderSource);

    // Image
    auto texture1 = Loader::getInstance()->loadTexture("../../texture/container2.png");
    auto texture2 = Loader::getInstance()->loadTexture("../../texture/container2_specular.png");

    // 10个立方体的位置
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    /*
    * 顶点坐标
    */
    float vertices[] = {
            // 顶点位置            // 法线向量           // 纹理坐标
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17,
            18, 19, 20,
            21, 22, 23,
            24, 25, 26,
            27, 28, 29,
            30, 31, 32,
            33, 34, 35
    };

    /* 使用一个独一无二的ID, 生成一个VBO对象 */
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /* 创建一个第一无二的ID， 生成一个VBO对象 */
    /* OpenGL的核心模式要求我们使用VAO，所以它知道该如何处理我们的定点输入 */
    /** 一个顶点数组会存储：**/
    /** glEnableVertexAttribArray和glDisableVertexAttribArray的调用 **/
    /** 通过glVertexAttribPointer设置的顶点属性配置 **/
    /** 通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象 **/
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* 将VBO绑定为顶点缓冲对象 */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /* 将顶点数据复制到顶点缓冲内存中*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* 设置顶点属性指针 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    /* 解绑VAO和VBO */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

    glm::mat4 trans;
    glm::mat4 model;      // 相对自身坐标系
    glm::mat4 view;       // 相对世界坐标系
    glm::mat4 projection; // 相对于摄像机
    auto cameraPos     = camera.getPosition();  // 摄像机位置
    auto lightPosition = glm::vec3(1.2f, 0.0f, 1.0f);
    auto radius        = (float)glm::sqrt(pow(lightPosition.x, 2) + pow(lightPosition.z, 2));

    /**
     * material
     * @link http://devernay.free.fr/cours/opengl/materials.html
     */
    auto mShininess    = 256.0f;

    /**
     * light
     */
    auto lAmbient      = glm::vec3(0.2f, 0.2f, 0.2f);
    auto lDiffuse      = glm::vec3(0.5f, 0.5f, 0.5f);
    auto lSpecular     = glm::vec3(1.0f, 1.0f, 1.0f);

    shaderProgram.use();
    shaderProgram.setVec3("viewPos", cameraPos);
    shaderProgram.setInt("material.diffuse", 0);
    shaderProgram.setInt("material.specular", 1);
    shaderProgram.setFloat("material.shininess", mShininess);
    shaderProgram.setVec3("light.ambient", lAmbient);
    shaderProgram.setVec3("light.diffuse", lDiffuse);
    shaderProgram.setVec3("light.specular", lSpecular);

    lightShaderProgram.use();
    lightShaderProgram.setVec3("light.ambient", lAmbient);
    lightShaderProgram.setVec3("light.diffuse", lDiffuse);
    lightShaderProgram.setVec3("light.specular", lSpecular);

    /*
     * - glfwWindowShouldClose 函数在每帧开始时会检测GLFW是否要退出
     * - glfwPollEvents 函数检查有没有触发事件(键盘输入、鼠标移动)，此时可以更新窗口状态
     * - glfwSwapBuffers 函数会交换颜色缓冲区
     */
    while(!glfwWindowShouldClose(window)) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
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
#ifdef DEBUG
        std::cout << "currentTime: " << currentTime << std::endl;
        std::cout << "deltaTime: " << deltaTime << std::endl;
        std::cout << "lastFrame: " << lastFrame << std::endl;
        std::cout << "FPS: " << (int)(1 / deltaTime) << std::endl;
#endif

        trans = glm::mat4();
        // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        // trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::mat4();
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));

        view = camera.getViewMatrix();

        projection = glm::perspective(glm::radians(camera.getFov()), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);

        lightPosition = glm::vec3(glm::cos(glfwGetTime()) * radius, lightPosition.y, fabs(glm::sin(glfwGetTime()) * radius));

        // lDiffuse = glm::vec3(sin(glfwGetTime()*2.0f), sin(glfwGetTime()*0.7f), sin(glfwGetTime()*1.3f)) * glm::vec3(0.5f);
        // lAmbient = lDiffuse * glm::vec3(0.2f);

        /*
         * 处理用户输入
         */
        processInput(window);

        /*
         * 渲染
         */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        /// object
        shaderProgram.use();
        for (int i = 0; i < 1; i++) {
            cameraPos = camera.getPosition();
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            if (i%3 == 0 || i == 0) {
//                model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f * (i + 1)), glm::vec3(1.0f, 1.0f, 1.0f));
                model = glm::rotate(model, glm::radians(20.0f * (i + 1)), glm::vec3(1.0f, 1.0f, 1.0f));
            }

            shaderProgram.setVec3("lightPos", lightPosition);
            shaderProgram.setMat4("transform", trans);
            shaderProgram.setMat4("model", model);
            shaderProgram.setMat4("view", view);
            shaderProgram.setMat4("projection", projection);
            shaderProgram.setVec3("viewPos", cameraPos);
            shaderProgram.setVec3("light.ambient", lAmbient);
            shaderProgram.setVec3("light.diffuse", lDiffuse);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        }

        /// light
        lightShaderProgram.use();
        trans = glm::mat4();

        model = glm::mat4();
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));

        lightShaderProgram.setMat4("transform", trans);
        lightShaderProgram.setMat4("model", model);
        lightShaderProgram.setMat4("view", view);
        lightShaderProgram.setMat4("projection", projection);
        lightShaderProgram.setVec3("light.ambient", lAmbient);
        lightShaderProgram.setVec3("light.diffuse", lDiffuse);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


        /// top left container
        shaderProgram.use();
        trans = glm::mat4();
        trans = glm::translate(trans, glm::vec3(-1.0f, 1.0f, 0.0f));
        trans = glm::scale(trans, glm::vec3(0.3f, 0.3f, 0.1f));
        model = glm::mat4();
        view  = glm::mat4();
        projection = glm::mat4();

        shaderProgram.setMat4("transform", trans);
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

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
