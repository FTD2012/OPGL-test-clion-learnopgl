set(APP_NAME 1.1_hello_window)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_window_learn1.cpp)
add_executable(1.1_hello_window ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(1.1_hello_window OPGL_test_clion)

target_link_libraries(1.1_hello_window ${TARGET_LIB})

