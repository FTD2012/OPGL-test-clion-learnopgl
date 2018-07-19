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

#include <Shader.h>
#include <Config.h>

float mixPercent = 0.2;

/*
 * 告诉OpenGL渲染窗口的尺寸(视口Viewport)
 * 当用户改变窗口大小时，视口也被对应调整
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixPercent = fmin(1.0f, mixPercent + 0.01f);
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixPercent = fmax(0.0f, mixPercent - 0.01f);
    }
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
    GLFWwindow *window = glfwCreateWindow(200, 150, "好好学习OPENGL", NULL, NULL);
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
    Shader shaderProgram(glm_vertexShaderSource, glm_fragmentShaderSource);

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


    /*
    * 顶点坐标
    */
    float vertices[] = {
            // 位置                  // 颜色                 // 纹理坐标
            0.5f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f,       1.0f, 1.0f,     // 右上
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,     // 右下
            -0.5f, -0.5, 0.0f,      0.0f, 0.0f, 1.0f,       0.0f, 0.0f,     // 左下
            -0.5f, 0.5f, 0.0f,      1.0f, 1.0f, 0.0f,       0.0f, 1.0f      // 左上
    };

    unsigned int indices[] = {
            0, 1, 3,    // 第一个三角形
            1, 2, 3     // 第二个三角形
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
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
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* 使用 填充模式 绘制 */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    shaderProgram.use();
    shaderProgram.setInt("texture1", 0);
    shaderProgram.setInt("texture2", 1);

    /*
     * MainLoop
     */


    /*
     * - glfwWindowShouldClose 函数在每帧开始时会检测GLFW是否要退出
     * - glfwPollEvents 函数检查有没有触发事件(键盘输入、鼠标移动)，此时可以更新窗口状态
     * - glfwSwapBuffers 函数会交换颜色缓冲区
     */
    while(!glfwWindowShouldClose(window)) {

        glm::mat4 trans;
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

        /*
         * 处理用户输入
         */
        processInput(window);

        /*
         * 渲染
         */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shaderProgram.use();
        shaderProgram.setFloat("mixPercent", mixPercent);
        shaderProgram.setMat("transform", trans);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
