//
// @name triangle_vertex_shader.vs
// @project OPGL_test_clion
// @author lvjiaming
// @date 2017/7/18-23:12
//

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
	gl_Position = transform * vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}