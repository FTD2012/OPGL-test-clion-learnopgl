set(APP_NAME 3.1_model)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        model.cpp
        MainScene.h
        MainScene.cpp
        )
add_executable(3.1_model ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(3.1_model OPGL_test_clion)

target_link_libraries(3.1_model ${TARGET_LIB})