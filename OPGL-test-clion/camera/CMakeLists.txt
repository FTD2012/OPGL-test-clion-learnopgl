set(APP_NAME camera)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES hello_camera.cpp)
add_executable(camera hello_camera.cpp)

TARGET_LINK_LIBRARIES(camera OPGL_test_clion)

target_link_libraries(camera ${TARGET_LIB})

