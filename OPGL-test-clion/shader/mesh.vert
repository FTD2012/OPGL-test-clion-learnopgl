const char *mesh_vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoord;
layout (location = 5) in mat4 aInstanceMatrix;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec3 Color;
    vec2 TexCoords;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform bool enableInstancing;

void main() {
    mat4 realModel;
    if (enableInstancing) {
        realModel = aInstanceMatrix;
    } else {
        realModel = model;
    }
    gl_Position = projection * view * realModel * vec4(aPos, 1.0f);
    vs_out.FragPos = vec3(realModel * vec4(aPos, 1.0f));
    vs_out.Normal = mat3(transpose(inverse(realModel))) * aNormal;
    vs_out.Color = vec3(1.0f);
    vs_out.TexCoords = aTexCoord;
}
)";
