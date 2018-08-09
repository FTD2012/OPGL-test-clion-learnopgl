set(APP_NAME 2.4_material_map)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        material_map.cpp
        )
add_executable(2.4_material_map ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(2.4_material_map OPGL_test_clion)

target_link_libraries(2.4_material_map ${TARGET_LIB})