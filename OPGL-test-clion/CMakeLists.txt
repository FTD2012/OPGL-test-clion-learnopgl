cmake_minimum_required(VERSION 3.7)
project(OPGL_test_clion)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp glad.c)
add_executable(OPGL_test_clion ${SOURCE_FILES})

include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/GLAD/glad)
include_directories(${PROJECT_SOURCE_DIR}/GLAD)
include_directories(/usr/local/Cellar/glfw/3.2.1/include)

set(TARGET_LIB
        "/usr/local/Cellar/glew/2.0.0/lib"
        "/usr/local/Cellar/glfw/3.2.1/lib"
        "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.2.0.0.dylib"
        "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib"
        )

find_package( OpenGL REQUIRED )
list( APPEND TARGET_LIB ${OPENGL_gl_LIBRARY} )

target_link_libraries(OPGL_test_clion ${TARGET_LIB})