set(APP_NAME hello_triangle)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_triangle_test_learn1.cpp)
add_executable(hello_triangle hello_triangle_learn1.cpp)

TARGET_LINK_LIBRARIES(hello_triangle OPGL_test_clion)

target_link_libraries(hello_triangle ${TARGET_LIB})

