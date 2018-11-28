const char *point_geometryShaderSource = R"(#version 330 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

// built in block
// in gl_Vertex {
//     vec4  gl_Position;
//     float gl_PointSize;
//     float gl_ClipDistance[];
// }

in vec4 color[];

out vec4 fColor;

void main()
{

    fColor = color[0];

    gl_Position = gl_in[0].gl_Position + vec4(-0.5, 0.0, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 0.5, 0.0, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
}
)";
