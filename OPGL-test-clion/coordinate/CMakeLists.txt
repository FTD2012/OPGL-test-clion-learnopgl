set(APP_NAME coordinate)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_coordinate.cpp)
add_executable(coordinate hello_coordinate.cpp)

TARGET_LINK_LIBRARIES(coordinate OPGL_test_clion)

target_link_libraries(coordinate ${TARGET_LIB})

