set(APP_NAME C++_base_test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(C++_base_test main.cpp)

TARGET_LINK_LIBRARIES(C++_base_test OPGL_test_clion)

target_link_libraries(C++_base_test ${TARGET_LIB})

