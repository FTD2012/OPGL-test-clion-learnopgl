set(APP_NAME 1.4_texture)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        texture.cpp
#        texture_test.cpp
        )
add_executable(1.4_texture ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(1.4_texture OPGL_test_clion)

target_link_libraries(1.4_texture ${TARGET_LIB})