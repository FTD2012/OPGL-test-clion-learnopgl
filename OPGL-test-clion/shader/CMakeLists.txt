set(APP_NAME shader)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_shader.cpp vs.vs)
add_executable(shader hello_shader.cpp shader.h shader.cpp vs.vs)

TARGET_LINK_LIBRARIES(shader OPGL_test_clion)

target_link_libraries(shader ${TARGET_LIB})

