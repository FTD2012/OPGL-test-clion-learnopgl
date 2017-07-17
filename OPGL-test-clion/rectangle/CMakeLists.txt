set(APP_NAME rectangle)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES rectangle.cpp)
add_executable(rectangle rectangle.cpp)

TARGET_LINK_LIBRARIES(rectangle OPGL_test_clion)

target_link_libraries(rectangle ${TARGET_LIB})

