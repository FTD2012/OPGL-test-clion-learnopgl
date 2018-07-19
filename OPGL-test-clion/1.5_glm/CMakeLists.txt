set(APP_NAME 1.5_glm)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        glm_test.cpp
        )
add_executable(1.5_glm ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(1.5_glm OPGL_test_clion)

target_link_libraries(1.5_glm ${TARGET_LIB})