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
#include <loader/Model.h>
#include <unordered_map>

int main (int argc, char **argv) {

    std::unordered_map<std::string, int> _textures;

    _textures.insert(std::make_pair("1", 3));

    auto index =  _textures.find("");

    std::cout << "111 = " << index->second << std::endl;

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

    unsigned int indices[] = {
            0, 1, 3,    // 第一个三角形
            1, 2, 3     // 第二个三角形
    };
    std::cout << "sizeof(indices) = " << sizeof(indices) << std::endl;





    return EXIT_SUCCESS;
}
