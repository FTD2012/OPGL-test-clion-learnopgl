//
// @name triangle_fragment_shader.fs
// @project OPGL_test_clion
// @author lvjiaming
// @date 2017/7/18-23:14
// @ref []
//

#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0f);
}