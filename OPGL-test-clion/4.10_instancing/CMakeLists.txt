set(APP_NAME 4.10_instancing)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.10_instancing.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.10_instancing ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.10_instancing OPGL_test_clion)

target_link_libraries(4.10_instancing ${TARGET_LIB})