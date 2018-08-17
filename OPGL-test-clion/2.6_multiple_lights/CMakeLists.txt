set(APP_NAME 2.6_multiple_lights)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        multiple_lights.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(2.6_multiple_lights ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(2.6_multiple_lights OPGL_test_clion)

target_link_libraries(2.6_multiple_lights ${TARGET_LIB})