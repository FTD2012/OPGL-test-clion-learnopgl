//
// Created by lvjiaming on 2018/5/9.
//

#ifndef OPGL_TEST_CLION_SHADER_H
#define OPGL_TEST_CLION_SHADER_H

#include <external/glad.h>
#include <string>
#include <iostream>

#define CHECK_GL_ERROR_DEBUG() \
    do { \
        GLenum __error = glGetError(); \
        if(__error) { \
            printf("OpenGL error 0x%04X in %s %s %d\n", __error, __FILE__, __FUNCTION__, __LINE__); \
        } \
    } while (false)

class Shader {
public:
    Shader(const char *vShaderCode, const char *fShaderCode);
    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    enum ShaderType {
        ShaderProgram,
        VertexShader,
        FragmentShader
    };

protected:
    unsigned int compileShader(const char *source, ShaderType type);
    bool checkCompileErrors(unsigned int shader, ShaderType type);

private:
    unsigned int shaderProgram;

};


#endif //OPGL_TEST_CLION_SHADER_H
