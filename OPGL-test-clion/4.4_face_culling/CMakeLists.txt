set(APP_NAME 4.4_face_culling)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        4.4_face_culling.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(4.4_face_culling ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(4.4_face_culling OPGL_test_clion)

target_link_libraries(4.4_face_culling ${TARGET_LIB})