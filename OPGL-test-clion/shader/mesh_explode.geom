const char *mesh_geometryShaderSource = R"(#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

// built in block
// in gl_Vertex {
//     vec4  gl_Position;
//     float gl_PointSize;
//     float gl_ClipDistance[];
// }

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec3 Color;
    vec2 TexCoords;
} gs_in[];

uniform float time;

out vec3 Normal;
out vec3 Color;
out vec3 FragPos;
out vec2 TexCoords;

vec3 getTriangleNormal() {
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 expolde(vec4 position, vec3 normal) {
    float magnitude = 2.0f;
    vec3 direction = normal * ((sin(30) + 1.0f) / 2.0f) * magnitude;
    return position + vec4(direction, 0.0f);
}

void main() {
    vec3 normal = getTriangleNormal();

    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            gl_Position = expolde(gl_in[i].gl_Position, normal);
        } else {
//            gl_Position = gl_in[i].gl_Position;
            gl_Position = expolde(gl_in[i].gl_Position, normal);
        }

        FragPos   = gs_in[i].FragPos;
        Normal    = gs_in[i].Normal;
        Color     = gs_in[i].Color;
        TexCoords = gs_in[i].TexCoords;
        EmitVertex();
    }

    EndPrimitive();


}
)";
