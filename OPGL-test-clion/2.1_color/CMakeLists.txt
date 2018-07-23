set(APP_NAME 2.1_color)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        color.cpp
        )
add_executable(2.1_color ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(2.1_color OPGL_test_clion)

target_link_libraries(2.1_color ${TARGET_LIB})