#cmake_minimum_required(VERSION 3.7)
#project(OPGL_test_clion)
#
#set(CMAKE_CXX_STANDARD 11)
#
#set(SOURCE_FILES main.cpp glad.c)
#add_executable(OPGL_test_clion ${SOURCE_FILES})
#
#include_directories(/usr/local/include)
#include_directories(${PROJECT_SOURCE_DIR}/GLAD/glad)
#include_directories(${PROJECT_SOURCE_DIR}/GLAD)
#include_directories(/usr/local/Cellar/glfw/3.2.1/include)
#
#set(TARGET_LIB
#        "/usr/local/Cellar/glew/2.0.0/lib"
#        "/usr/local/Cellar/glfw/3.2.1/lib"
#        "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.2.0.0.dylib"
#        "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib"
#        )
#
#find_package( OpenGL REQUIRED )
#list( APPEND TARGET_LIB ${OPENGL_gl_LIBRARY} )
#
#target_link_libraries(OPGL_test_clion ${TARGET_LIB})

project(OPGL_test_clion)
cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/shader)
include_directories(texture)
include_directories(/usr/local/Cellar/glfw/3.2.1/include)


# brew install glfw
set(TARGET_LIB
        "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib"
        )

find_package( OpenGL REQUIRED )
list( APPEND TARGET_LIB ${OPENGL_gl_LIBRARY} )

LINK_DIRECTORIES(${TARGET_LIB})


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



ADD_SUBDIRECTORY(base)
#ADD_SUBDIRECTORY(GLAD)
ADD_SUBDIRECTORY(1.1_hello_window)
ADD_SUBDIRECTORY(C++_base_test)
ADD_SUBDIRECTORY(1.2_hello_triangle)
ADD_SUBDIRECTORY(1.3_hello_shader)
ADD_SUBDIRECTORY(1.4_texture)
ADD_SUBDIRECTORY(1.5_glm)


#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)



