//
// Created by lvjiaming on 2018/5/9.
//

#ifndef OPGL_TEST_CLION_CONFIG_H
#define OPGL_TEST_CLION_CONFIG_H

extern const char *line_vertexShaderSource;
extern const char *line_fragmentShaderSource;
extern const char *hello_triangle_fragmentShaderSource;
extern const char *hello_triangle_vertexShaderSource;
extern const char *texture_vertexShaderSource;
extern const char *texture_fragmentShaderSource;
extern const char *glm_fragmentShaderSource;
extern const char *glm_vertexShaderSource;
extern const char *coordinate_system_fragmentShaderSource;
extern const char *coordinate_system_vertexShaderSource;
extern const char *camera_fragmentShaderSource;
extern const char *camera_vertexShaderSource;
extern const char *color_fragmentShaderSource;
extern const char *color_vertexShaderSource;
extern const char *color_light_fragmentShaderSource;
extern const char *basic_lighting_vertexShaderSource;
extern const char *basic_lighting_fragmentShaderSource;
extern const char *material_light_fragmentShaderSource;
extern const char *material_map_vertexShaderSource;
extern const char *material_map_fragmentShaderSource;
extern const char *light_caster_vertexShaderSource;
extern const char *light_caster_fragmentShaderSource;
extern const char *cube_vertexShaderSource;
extern const char *cube_fragmentShaderSource;
extern const char *mesh_vertexShaderSource;
extern const char *mesh_fragmentShaderSource;
extern const char *single_color_vertexShaderSource;
extern const char *single_color_fragmentShaderSource;


/**
 * @property {int} FPS 刷新帧数
 */
extern int FPS;

/**
 * @property {float} frameSecond 每帧间隔时间
 */
extern float frameSecond;

/**
 * @property {float} deltaTime 当前帧与上一帧的时间差
 * @property {float} lastFrame 上一帧的时间
 */
extern float deltaTime;
extern float lastFrame;

/**
 * @property {int} ScreenWidth  屏幕宽度(Pixel)
 * @property {int} ScreenHeight 屏幕高度(Pixel)
 */
extern const int ScreenWidth;
extern const int ScreenHeight;

#endif //OPGL_TEST_CLION_CONFIG_H