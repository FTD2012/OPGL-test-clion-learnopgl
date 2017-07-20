set(APP_NAME texture)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_texture.cpp)
add_executable(texture hello_texture.cpp ../openl_lib/shader.h)

TARGET_LINK_LIBRARIES(texture OPGL_test_clion)

target_link_libraries(texture ${TARGET_LIB})

