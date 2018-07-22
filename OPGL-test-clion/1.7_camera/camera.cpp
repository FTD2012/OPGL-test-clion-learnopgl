//
// Created by invoker on 2018/05/10.
//

//#define STB_IMAGE_IMPLEMENTATION
#include <external/stb_image.h>
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
 * @property {float} cameraSpeed 相机移动速度
 */
float cameraSpeed = 2.5f;

/**
 * @property {float} mixPercent 图片颜色混合比例
 */
float mixPercent = 0.2f;

/**
 * @property {int} ScreenWidth  屏幕宽度(Pixel)
 * @property {int} ScreenHeight 屏幕高度(Pixel)
 */
const int ScreenWidth = 1920;
const int ScreenHeight = 1080;

/**
 * 摄像机属性
 * @property {glm::vec3} cameraPos   摄像机在世界坐标系中的位置
 * @property {glm::vec3} cameraFront 摄像机观察的位置
 * @property {glm::vec3} cameraUp    摄像机上方
 */
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

/**
 * 默认光标位置
 * @property {float} lastCursorX
 * @property {float} lastCursorY
 * @property {bool} firstMouse 鼠标位置是否初始化
 */
float lastCursorX;
float lastCursorY;
bool firstMouse = true;

/**
 * 俯仰角(Pitch)、偏航角(Yaw)、滚转角(Roll)
 * @property {float} Pitch
 * @property {float} Yaw
 * @property {float} Roll
 */
float Pitch = 0.0f;
float Yaw = -90.0f;
//float Roll = 0;

/**
 * 摄像机的视角方位(field of view)
 */
float FOV = 45.0f;


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
        mixPercent = fmin(1.0f, mixPercent + 0.01f);
    }
    // down
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixPercent = fmax(0.0f, mixPercent - 0.01f);
    }
    // w
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    // s
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    // a
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
    }
    // d
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
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

    auto sensitivity = 0.2f;
    auto xOffset = (float)(xPos - lastCursorX);
    auto yOffset = (float)(lastCursorY - yPos);
    lastCursorX = (float)xPos;
    lastCursorY = (float)yPos;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    Pitch += yOffset;
    Yaw   += xOffset;

    Pitch = (Pitch > 89.0f) ? 89.0f : ((Pitch < -89.0f) ? -89.0f : Pitch);

    glm::vec3 front;
    front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
    front.y = sin(glm::radians(Pitch));
    front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
    cameraFront = glm::normalize(front);
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

    FOV -= yOffset;
    FOV = (FOV < 1.0f) ? 1.0f : ((FOV > 45.0f) ? 45.0f : FOV);
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
    Shader shaderProgram(camera_vertexShaderSource, camera_fragmentShaderSource);

    // Image
    /* 使用'stb_image.h'的API把一张图片加载到内存中 */
    unsigned int texture1, texture2;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../../texture/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        /* 使用一个独一无二的ID，生成一个纹理对象 */
        glGenTextures(1, &texture1);
        /* 将texture绑定为2D纹理对象 */
        glBindTexture(GL_TEXTURE_2D, texture1);

        /* 设置纹理的环绕模式为GL_REPEAT
         * GL_REPEAT: 对纹理的默认行为，重复纹理图像。
         * GL_MIRRORED_REPEAT: 和GL_REPEAT一样，但每次重复图片是镜像的。
         * GL_CLAMP_TO_EDGE: 纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
         * GL_CLAMP_TO_BORDER: 超出的坐标为用户指定的边缘颜色。
         * s => x
         * t => y
         * r => z
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        /* 设置纹理的过滤模式(进行放大和缩小操作时)为GL_LINEAR
         * GL_NEAREST: 临近过滤(Nearest Neighbor Filtering)，选择离中心店最近的纹理坐标的像素。
         * GL_LINEAR: 线性过滤((Bi)linear Filtering)，基于纹理坐标附近的纹理像素，计算出相应的插值，距离中心越近，权重越大。
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /* 将图片数据生成一个纹理 */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        /* 生成多级渐远纹理(Mipmap) */
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture1" << std::endl;
        return EXIT_FAILURE;
    }
    stbi_image_free(data);

    data = stbi_load("../../texture/face.png", &height, &width, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture2" << std::endl;
        return EXIT_FAILURE;
    }
    stbi_image_free(data);

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
            // 位置               // 纹理坐标
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

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

    /* 将定点数据复制到顶点缓冲内存中*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* 设置定点属性指针 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    /* 解绑VAO和VBO */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /**
     * 使用 线框模式(Wireframe Mode) 绘制
     * 配置OpenGl如何绘制图元
     * @param1: 将配置应用到三角形的正面和背面
     * @param2: 使用线来绘制
     */
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* 使用 填充模式 绘制 */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shaderProgram.use();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);

    /*
     * MainLoop
     */

    glm::mat4 trans;
    glm::mat4 model;      // 相对自身坐标系
    glm::mat4 view;       // 相对世界坐标系
    glm::mat4 projection; // 相对于摄像机

//    glm::vec3 cameraPosition;   // 摄像机位置
//    glm::vec3 cameraTarget;     // 摄像机指向的目标
//    glm::vec3 cameraDirection;  // 摄像机的z轴正方向（与指向的方向相反）
//
//    glm::vec3 up;               // 上向量(Up Vector)
//    glm::vec3 cameraRight;      // 摄像机x轴正方向
//
//    glm::vec3 cameraUp;         // 摄像机y轴正方向
//
//    // 摄像机z轴正方向
//    cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
//    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//    cameraDirection = glm::normalize(cameraPosition - cameraTarget);    // 向量相减，指向被减 cameraTarget => cameraPosition
//
//    // 摄像机x轴正方向
//    up = glm::vec3(0.0f, 1.0f, 0.0f);
//    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//
//    // 摄像机y轴正方向
//    cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));



    glEnable(GL_DEPTH_TEST);

    /*
     * - glfwWindowShouldClose 函数在每帧开始时会检测GLFW是否要退出
     * - glfwPollEvents 函数检查有没有触发事件(键盘输入、鼠标移动)，此时可以更新窗口状态
     * - glfwSwapBuffers 函数会交换颜色缓冲区
     */
    while(!glfwWindowShouldClose(window)) {

        // frame time
        auto currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastFrame;
        if (deltaTime < frameSecond) {
            usleep((unsigned int)((frameSecond-deltaTime)*10e3));
            continue;
        }
        lastFrame = currentTime;
        cameraSpeed = 2.5f * deltaTime;

        // std::cout << "currentTime: " << currentTime << std::endl;
        // std::cout << "deltaTime: " << deltaTime << std::endl;
        // std::cout << "lastFrame: " << lastFrame << std::endl;
        // std::cout << "FPS: " << (int)(1 / deltaTime) << std::endl;

        trans = glm::mat4();
        // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        // trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::mat4();
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));

        view = glm::mat4();
        view = glm::lookAt(                 // 摄像机将永远注视前方
                cameraPos,                  // camera position
                cameraPos + cameraFront,    // camera target
                cameraUp                    // up
        );

        projection = glm::perspective(glm::radians(FOV), (float)ScreenWidth / ScreenHeight, 0.1f, 100.0f);

        /*
         * 处理用户输入
         */
        processInput(window);

        /*
         * 渲染
         */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shaderProgram.use();
        glBindVertexArray(VAO);

        for (int i = 0; i < 10; i++) {
            model = glm::mat4();
            model = glm::translate(model, cubePositions[i]);
            if (i%3 == 0 || i == 0) {
                model = glm::rotate(model, (float) glfwGetTime() * glm::radians(20.0f * (i + 1)), glm::vec3(1.0f, 1.0f, 1.0f));
            }

            shaderProgram.setFloat("mixPercent", mixPercent);
            shaderProgram.setMat4("transform", trans);
            shaderProgram.setMat4("model", model);
            shaderProgram.setMat4("view", view);
            shaderProgram.setMat4("projection", projection);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        }


        /// second container
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
