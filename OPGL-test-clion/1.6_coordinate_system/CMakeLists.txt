set(APP_NAME 1.6_coordinate_system)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        coordinate_system.cpp
        )
add_executable(1.6_coordinate_system ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(1.6_coordinate_system OPGL_test_clion)

target_link_libraries(1.6_coordinate_system ${TARGET_LIB})