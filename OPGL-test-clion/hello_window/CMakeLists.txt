set(APP_NAME hello_window)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_window_test.cpp)
add_executable(hello_window hello_window_test.cpp)

TARGET_LINK_LIBRARIES(hello_window OPGL_test_clion)

target_link_libraries(hello_window ${TARGET_LIB})

