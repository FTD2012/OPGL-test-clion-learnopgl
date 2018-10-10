set(APP_NAME 4.3_blending)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.3_blending.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.3_blending ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.3_blending OPGL_test_clion)

target_link_libraries(4.3_blending ${TARGET_LIB})