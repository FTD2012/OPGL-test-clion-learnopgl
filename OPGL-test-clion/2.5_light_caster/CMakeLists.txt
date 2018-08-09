set(APP_NAME 2.5_light_caster)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        light_caster.cpp
        )
add_executable(2.5_light_caster ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(2.5_light_caster OPGL_test_clion)

target_link_libraries(2.5_light_caster ${TARGET_LIB})