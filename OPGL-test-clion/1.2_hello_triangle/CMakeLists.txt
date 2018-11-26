set(APP_NAME 1.2_hello_triangle)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_triangle_learn1.cpp)
add_executable(1.2_hello_triangle hello_triangle_learn1.cpp)

TARGET_LINK_LIBRARIES(1.2_hello_triangle OPGL_test_clion)

target_link_libraries(1.2_hello_triangle ${TARGET_LIB})

