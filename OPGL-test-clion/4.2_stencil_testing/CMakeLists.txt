set(APP_NAME 4.2_stencil_testing)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.2_stencil_testing.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.2_stencil_testing ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.2_stencil_testing OPGL_test_clion)

target_link_libraries(4.2_stencil_testing ${TARGET_LIB})