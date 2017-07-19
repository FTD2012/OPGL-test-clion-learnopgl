/*
 * @name fs.fs
 * @project OPGL_test_clion
 * @author lvjiaming
 * @date 2017/7/19-00:32
 * @ref []
 */

  #version 330 core
  out vec4 FragColor;
  in vec3 ourColor;

  void main()
  {
      FragColor = vec4(ourColor, 1.0);
  }