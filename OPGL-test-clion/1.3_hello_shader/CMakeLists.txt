set(APP_NAME 1.3_hello_shader)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_shader.cpp)
add_executable(1.3_hello_shader hello_shader.cpp)

TARGET_LINK_LIBRARIES(1.3_hello_shader OPGL_test_clion)

target_link_libraries(1.3_hello_shader ${TARGET_LIB})

