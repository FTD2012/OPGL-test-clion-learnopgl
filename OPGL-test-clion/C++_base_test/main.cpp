/*
 * @name main.cpp
 * @project OPGL_test_clion
 * @author lvjiaming
 * @date 2017/7/18-16:09
 * @ref []
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main (int argc, char **argv) {

    std::ifstream fin;
    fin.open("/Users/lvjiaming/WorkSpace/OPGL/OPGL-test-clion-learnopgl/OPGL-test-clion/shader/CMakeLists.txt");
    if (!fin.is_open()) {
        std::cout << "fin is not open" << std::endl;

    }

    std::stringstream vShaderStream;
    // read file's buffer contents into streams
    vShaderStream << fin.rdbuf();

    fin.close();
    // convert stream into string
    std::string vertexCode = vShaderStream.str();
    std::cout << "vertexCode = " << vertexCode << std::endl;



    return EXIT_SUCCESS;
}
