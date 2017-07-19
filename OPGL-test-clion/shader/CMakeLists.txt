set(APP_NAME shader)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_shader.cpp)
add_executable(shader hello_shader.cpp ../openl_lib/shader.h shader.cpp)

TARGET_LINK_LIBRARIES(shader OPGL_test_clion)

target_link_libraries(shader ${TARGET_LIB})

