//
// @name triangle_vertex_shader.vs
// @project OPGL_test_clion
// @author lvjiaming
// @date 2017/7/30-13:07
//

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
}