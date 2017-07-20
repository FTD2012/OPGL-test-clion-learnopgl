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
include_directories(${PROJECT_SOURCE_DIR}/GLAD/glad)
include_directories(${PROJECT_SOURCE_DIR}/GLAD)
include_directories(/usr/local/Cellar/glfw/3.2.1/include)


set(TARGET_LIB
        "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.2.0.0.dylib"
        "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib"
        )

find_package( OpenGL REQUIRED )
list( APPEND TARGET_LIB ${OPENGL_gl_LIBRARY} )

LINK_DIRECTORIES(${TARGET_LIB})

if(hello_window)
    add_subdirectory(hellow_window)
endif(hello_window)

if(hello_triangle)
    add_subdirectory(hello_triangle)
endif(hello_triangle)

if(rectangle)
    add_subdirectory(rectangle)
endif(rectangle)

if(C++_base_test)
    add_subdirectory(C++_base_test)
endif(C++_base_test)

if(shader)
    add_subdirectory(shader)
endif(shader)

if(texture)
    add_subdirectory(texture)
endif(texture)

ADD_SUBDIRECTORY(openl_lib)
ADD_SUBDIRECTORY(hello_window)
ADD_SUBDIRECTORY(hello_triangle)
ADD_SUBDIRECTORY(rectangle)
ADD_SUBDIRECTORY(C++_base_test)
ADD_SUBDIRECTORY(shader)
ADD_SUBDIRECTORY(texture)

#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)



