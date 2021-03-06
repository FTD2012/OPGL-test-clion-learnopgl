const char *color_vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 ourPosition;
uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    gl_Position = transform * projection * view * model * vec4(aPos, 1.0);
    ourPosition = vec4(aPos, 1.0f);
}
)";
