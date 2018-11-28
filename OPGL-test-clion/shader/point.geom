const char *point_geometryShaderSource = R"(#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

// built in block
// in gl_Vertex {
//     vec4  gl_Position;
//     float gl_PointSize;
//     float gl_ClipDistance[];
// }

in vec4 color[];
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 fColor;

void MPV_Transalte(mat4 mvp, vec4 position) {
    gl_Position = mvp * position;
}

void build_house(vec4 position) {

    mat4 mvp = projection * view * model;

    MPV_Transalte(mvp, position + vec4(-0.2, -0.2, 0.0, 0.0));    // 1:左下
    fColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);                        // white
    EmitVertex();
    MPV_Transalte(mvp, position + vec4( 0.2, -0.2, 0.0, 0.0));    // 2:右下
    fColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);                        // red
    EmitVertex();
    MPV_Transalte(mvp, position + vec4(-0.2,  0.2, 0.0, 0.0));    // 3:左上
    fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);                        // green
    EmitVertex();
    MPV_Transalte(mvp, position + vec4( 0.2,  0.2, 0.0, 0.0));    // 4:右上
    fColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);                        // blue
    EmitVertex();
    MPV_Transalte(mvp, position + vec4( 0.0,  0.4, 0.0, 0.0));    // 5:顶部
    fColor = color[0];                                            // origin
    EmitVertex();

    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
}
)";
