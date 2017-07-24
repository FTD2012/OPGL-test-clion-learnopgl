/*
 * @name hello_matrix.cpp
 * @project OPGL_test_clion
 * @author lvjiaming
 * @date 2017/7/24-16:46
 * @ref []
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main(int argc, char ** argv) {

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans;
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << vec.w << std::endl;



    return EXIT_SUCCESS;
}