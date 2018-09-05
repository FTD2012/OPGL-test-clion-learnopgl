//
// Created by lvjiaming on 2018/8/14.
//

#include <Config.h>


// line
#include <line.vert>
#include <line.frag>

// single color
#include <single_color.vert>
#include <single_color.frag>

// 1.3 shader
#include <hello_shader.frag>
#include <hello_shader.vert>

// 1.4 texture
#include <texture.vert>
#include <texture.frag>

// 1.5 glm
#include <glm.frag>
#include <glm.vert>

// 1.6 coordinate system
#include <coordinate_system.frag>
#include <coordinate_system.vert>

// 1.7 camera
#include <camera.frag>
#include <camera.vert>

// 2.1 color
#include <color.frag>
#include <color.vert>
#include <color_light.frag>

// 2.2 basic_lighting
#include <basic_lighting.vert>
#include <basic_lighting.frag>

// 2.3 material
#include <material_light.frag>

// 2.4 material map
#include <material_map.vert>
#include <material_map.frag>

// 2.5 light caster
#include <light_caster.vert>
#include <light_caster.frag>

// 2.6 multiple lights
#include <cube.vert>
#include <cube.frag>

// 3.1 model
#include <mesh.vert>
#include <mesh.frag>

int FPS = 60;
float frameSecond = 1.0f/FPS;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
const int ScreenWidth = 800;
const int ScreenHeight = 600;