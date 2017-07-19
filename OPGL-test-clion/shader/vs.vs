/*
 * @name vs.vs
 * @project OPGL_test_clion
 * @author lvjiaming
 * @date 2017/7/19-00:32
 * @ref []
 */

 #version 330 core
 layout (location = 0) in vec3 aPos;
 layout (location = 1) in vec3 aColour;

 out vec3 ourColor;

 void main()
 {
     gl_Position = vec4(aPos, 1.0);
     ourColor = aColour;
 }