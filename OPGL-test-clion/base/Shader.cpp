//
// Created by lvjiaming on 2018/5/9.
//

#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Macro.h"

Shader::Shader(const char *vShaderCode, const char *fShaderCode, const char *gShaderCode)
: _enableGeometryShader(false)
{

    /*
     * @deprecated
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream vShaderStream, fShaderStream;
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentCode);

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        vShaderFile.close();
        fShaderFile.close();

    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
     */

    _vertexShader = vShaderCode;
    _fragmentShader = fShaderCode;

    if (gShaderCode) {
        _geometryShader = gShaderCode;
        _enableGeometryShader = (bool) gShaderCode;
    }

    // 2. compile the source code
    link();

}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::link() {
    do {
        unsigned int vertexShader, fragmentShader, geometry = 0;

        vertexShader = compileShader(_vertexShader.c_str(), ShaderType::VertexShader);
        ASSERT(vertexShader, "Invalid vertex shader");

        fragmentShader = compileShader(_fragmentShader.c_str(), ShaderType::FragmentShader);
        ASSERT(fragmentShader, "Invalid fragment shader");

        if (_enableGeometryShader) {
            geometry = compileShader(_geometryShader.c_str(), ShaderType::GeometryShader);
            ASSERT(geometry, "Invalid geometry shader");
        }

        glDeleteProgram(shaderProgram);
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        if (geometry) {
            glAttachShader(shaderProgram, geometry);
        }
        glLinkProgram(shaderProgram);
        if (!checkCompileErrors(shaderProgram, ShaderType::ShaderProgram)) break;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        if (geometry) {
            glDeleteShader(geometry);
        }

    } while(0);
}

void Shader::use() {
    glUseProgram(shaderProgram);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}


void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

unsigned int Shader::compileShader(const char *source, Shader::ShaderType type) {
    unsigned int shader;
    switch (type) {
        case ShaderType::VertexShader:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;

        case ShaderType::GeometryShader:
            shader = glCreateShader(GL_GEOMETRY_SHADER);
            break;

        case ShaderType::FragmentShader:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;

        default:
            shader = 0;
    }

    if (!shader) return (unsigned int)false;
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    return checkCompileErrors(shader, type) ? shader : (unsigned int)false;
}

bool Shader::checkCompileErrors(unsigned int shader, Shader::ShaderType type) {
    int status;
    char infoLog[1024];
    switch (type) {
        case ShaderType::VertexShader:
        case ShaderType::FragmentShader:
        case ShaderType::GeometryShader:
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (!status) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            return (status == GL_TRUE);

        case ShaderType::ShaderProgram:
            glGetProgramiv(shader, GL_LINK_STATUS, &status);
            if (!status) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
            return (status == GL_TRUE);

        default:
            return GL_FALSE;
    }
}

const char *Shader::getVertexShader() const {
    return _vertexShader.c_str();
}

void Shader::setVertexShader(const std::string &vertexShader) {
    _vertexShader = _vertexShader;
    link();
}

const char *Shader::getFragmentShader() const {
    return _fragmentShader.c_str();
}

void Shader::setFragmentShader(const std::string &fragmentShader) {
    _fragmentShader = fragmentShader;
    link();
}
























