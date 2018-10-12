set(APP_NAME 4.5_frame_buffer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.5_frame_buffer.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.5_frame_buffer ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.5_frame_buffer OPGL_test_clion)

target_link_libraries(4.5_frame_buffer ${TARGET_LIB})