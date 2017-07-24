//
// @name triangle_vertex_shader.vs
// @project OPGL_test_clion
// @author lvjiaming
// @date 2017/7/18-23:12
//

#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0
layout (location = 1) in vec3 aColour; // 颜色变量的属性位置值为 1

uniform float offsetX;

out vec3 ourColor; // 向片段着色器输出一个颜色
out vec4 ourPosition;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourPosition = gl_Position;
    ourColor = aColour; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
}