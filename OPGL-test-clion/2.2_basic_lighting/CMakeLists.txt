set(APP_NAME 2.2_basic_lighting)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        basic_lighting.cpp
        )
add_executable(2.2_basic_lighting ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(2.2_basic_lighting OPGL_test_clion)

target_link_libraries(2.2_basic_lighting ${TARGET_LIB})