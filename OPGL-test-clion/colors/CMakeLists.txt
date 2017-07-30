set(APP_NAME colors)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_colors.cpp)
add_executable(colors hello_colors.cpp)

TARGET_LINK_LIBRARIES(colors OPGL_test_clion)

target_link_libraries(colors ${TARGET_LIB})

