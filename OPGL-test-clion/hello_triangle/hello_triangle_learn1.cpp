//
// Created by invoker on 2018/4/24.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}";

const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor\n;"
        "void main()\n"
        "{"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
        "}";


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
    GLFWwindow *window = glfwCreateWindow(800, 600, "好好学习OPENGL", NULL, NULL);
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

    /* 创建一个顶点着色器(vertex shader) */
    unsigned vertexShader = glCreateShader(GL_VERTEX_SHADER);
    /* 编译着色器 */
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    /* 编译是否成功？*/
    int sucess;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "error::shader::vertex::compilation_failed\n" << infoLog << std::endl;
    }

    /* 创建一个片段着色器 */
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    /* 编译着色器 */
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    /* 编译是否成功 */
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "error::shader::fragment::compilation_failed\n" << infoLog << std::endl;
    }

    /* 创建一个着色器对象(Shader Program Object) */
    unsigned int shaderProgram = glCreateProgram();
    /* 连接着色器 */
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    /* 编译是否成功 */
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "error::shader::program::compilation_failed\n" << infoLog << std::endl;
    }

    /* 使用编译好的着色器对象 */
    glUseProgram(shaderProgram);

    /*
    * 顶点坐标
    */
    float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
    };
    float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
    };

    /* 可以在同一时间生成多个VAO和VBO对象 */
    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // first triangle
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // second triangle
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
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

    /* 删除着色器 */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glfwTerminate();
    return 0;
}
