/*
 * @name main.cpp
 * @project OPGL_test_clion
 * @author lvjiaming
 * @date 2017/7/18-16:09
 * @ref []
 */


#include <iostream>
const char *fragmentShaderSource = "#version 330 core\n" "#3333#\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

int main (int argc, char **argv) {

    std::cout << "fragmentShaderSource = " << fragmentShaderSource << std::endl;

    return EXIT_SUCCESS;
}
