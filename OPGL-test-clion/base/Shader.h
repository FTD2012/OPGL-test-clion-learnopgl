//
// Created by lvjiaming on 2018/5/9.
//

#ifndef OPGL_TEST_CLION_SHADER_H
#define OPGL_TEST_CLION_SHADER_H

#include <external/glad.h>
#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>
#include <string>
#include <iostream>

class Shader {
public:
    Shader(const char *vShaderCode, const char *fShaderCode, const char *gShaderCode = nullptr);
    ~Shader();
    void link();
    void use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &vec) const;
    void setVec3(const std::string &name, float x, float y, float z) const;

    const char *getVertexShader() const;
    const char *getFragmentShader() const;
    void setVertexShader(const std::string &vertexShader);
    void setFragmentShader(const std::string &fragmentShader);

    enum ShaderType {
        ShaderProgram,
        VertexShader,
        FragmentShader,
        GeometryShader
    };

protected:
    unsigned int compileShader(const char *source, ShaderType type);
    bool checkCompileErrors(unsigned int shader, ShaderType type);

private:
    unsigned int shaderProgram;
    bool         _enableGeometryShader;
    std::string  _vertexShader;
    std::string  _fragmentShader;
    std::string  _geometryShader;

};


#endif //OPGL_TEST_CLION_SHADER_H
