set(APP_NAME 4.6_cube_map)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.6_cube_map.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.6_cube_map ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.6_cube_map OPGL_test_clion)

target_link_libraries(4.6_cube_map ${TARGET_LIB})