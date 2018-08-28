#
# @link https://www.cnblogs.com/hustdc/p/6692284.html
#

project(OPGL_test_clion)
cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/shader)
include_directories(texture)
include_directories(/usr/local/Cellar/glfw/3.2.1/include)


# brew install glfw
# brew install assimp
set(TARGET_LIB
        "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib"
        "/usr/local/Cellar/assimp/4.1.0/lib/libassimp.4.1.0.dylib"
        )

find_package( OpenGL REQUIRED )
list( APPEND TARGET_LIB ${OPENGL_gl_LIBRARY} )
link_libraries(${TARGET_LIB})

if(1.1_hello_window)
    add_subdirectory(1.1_hellow_window)
endif(1.1_hello_window)

if(C++_base_test)
    add_subdirectory(C++_base_test)
endif(C++_base_test)

if(1.2_hello_triangle)
    add_subdirectory(1.2_hello_triangle)
endif(1.2_hello_triangle)

if(1.3_hello_shader)
    add_subdirectory(1.3_hello_shader)
endif(1.3_hello_shader)

if(1.4_texture)
    add_subdirectory(1.4_texture)
endif(1.4_texture)

if(1.5_glm)
    add_subdirectory(1.5_glm)
endif(1.5_glm)

if (1.6_coordinate_system)
    add_subdirectory(1.6_coordinate_system)
endif(1.6_coordinate_system)

if (1.7_camera)
    add_subdirectory(1.7_camera)
endif(1.7_camera)

if (2.1_color)
    add_subdirectory(2.1_color)
endif(2.1_color)

if (2.2_basic_lighting)
    add_subdirectory(2.2_basic_lighting)
endif(2.2_basic_lighting)

if (2.4_material_map)
    add_subdirectory(2.4_material_map)
endif(2.4_material_map)

if (2.5_light_caster)
    add_subdirectory(2.5_light_caster)
endif(2.5_light_caster)

if (2.6_multiple_lights)
    add_subdirectory(2.6_multiple_lights)
endif(2.6_multiple_lights)

if (3.1_model)
    add_subdirectory(3.1_model)
endif(3.1_model)

if (4.1_depth_testing)
    add_subdirectory(4.1_depth_testing)
endif(4.1_depth_testing)

ADD_SUBDIRECTORY(base)
#ADD_SUBDIRECTORY(GLAD)
ADD_SUBDIRECTORY(1.1_hello_window)
ADD_SUBDIRECTORY(C++_base_test)
ADD_SUBDIRECTORY(1.2_hello_triangle)
ADD_SUBDIRECTORY(1.3_hello_shader)
ADD_SUBDIRECTORY(1.4_texture)
ADD_SUBDIRECTORY(1.5_glm)
ADD_SUBDIRECTORY(1.6_coordinate_system)
ADD_SUBDIRECTORY(1.7_camera)
ADD_SUBDIRECTORY(2.1_color)
ADD_SUBDIRECTORY(2.2_basic_lighting)
ADD_SUBDIRECTORY(2.4_material_map)
ADD_SUBDIRECTORY(2.5_light_caster)
ADD_SUBDIRECTORY(2.6_multiple_lights)
ADD_SUBDIRECTORY(3.1_model)
ADD_SUBDIRECTORY(4.1_depth_testing)


#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)



