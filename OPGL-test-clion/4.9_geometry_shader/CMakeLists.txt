set(APP_NAME 4.9_geometry_shader)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.9_geometry_shader.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.9_geometry_shader ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.9_geometry_shader OPGL_test_clion)

target_link_libraries(4.9_geometry_shader ${TARGET_LIB})