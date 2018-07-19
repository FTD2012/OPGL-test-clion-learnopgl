set(APP_NAME 1.7_camera)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        camera.cpp
        )
add_executable(1.7_camera ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(1.7_camera OPGL_test_clion)

target_link_libraries(1.7_camera ${TARGET_LIB})