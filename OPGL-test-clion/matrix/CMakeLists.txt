set(APP_NAME matrix)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_matrix.cpp)
add_executable(matrix hello_matrix.cpp)

TARGET_LINK_LIBRARIES(matrix OPGL_test_clion)

target_link_libraries(matrix ${TARGET_LIB})

