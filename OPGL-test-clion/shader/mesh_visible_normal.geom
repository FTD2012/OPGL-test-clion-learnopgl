const char *mesh_visible_normal_geometryShaderSource = R"(#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

const float MAGNITUDE = 0.04;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec3 Color;
    vec2 TexCoords;
} gs_in[];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

out vec3 Normal;
out vec3 Color;
out vec3 FragPos;
out vec2 TexCoords;

void generateLine(int index) {
    vec3 normal = normalize(vec3(projection * view * vec4(gs_in[index].Normal, 0.0f)));

    gl_Position = gl_in[index].gl_Position;
    EmitVertex();

    gl_Position = gl_in[index].gl_Position + vec4(normal, 0.0f) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();

}

void main() {
    for (int i = 0; i < 3; i++) {
        generateLine(i);
    }
}



)";