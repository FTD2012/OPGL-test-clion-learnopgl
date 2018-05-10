//
// Created by invoker on 2018/4/24.
//

#include <external/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <Shader.h>
#include <Config.h>

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

    Shader shaderProgram(hello_triangle_vertexShaderSource, hello_triangle_fragmentShaderSource);

    /*
    * 顶点坐标
    */
    float vertices[] = {
            // 位置                  // 颜色
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
            0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 1.0f
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

    /* 将VBO绑定为顶点缓冲对象 */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    /* 将定点数据复制到顶点缓冲内存中*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* 设置定点属性指针 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
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



    /*
     * MainLoop
     */

    /*
     * - glfwWindowShouldClose 函数在每帧开始时会检测GLFW是否要退出
     * - glfwPollEvents 函数检查有没有触发事件(键盘输入、鼠标移动)，此时可以更新窗口状态
     * - glfwSwapBuffers 函数会交换颜色缓冲区
     */
    while(!glfwWindowShouldClose(window)) {

        /*
         * 处理用户输入
         */
        processInput(window);

        /*
         * 渲染
         */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        shaderProgram.setFloat("xOffset", 0.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
    return 0;
}
