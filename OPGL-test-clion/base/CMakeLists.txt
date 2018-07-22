# CMakeLists for src directory
PROJECT(OPGL_test_clion)

SET(OPGL_test_clion_SRCS
        external
        external/khrplatform.h
        external/glad.h
        external/glad.c
        external/stb_image.h
        external/glm
        camera/camera.h
        camera/camera.cpp
        Config.h
        Shader.h
        Shader.cpp
        Macro.h
        )

# shared library
ADD_LIBRARY(OPGL_test_clion SHARED ${OPGL_test_clion_SRCS})

# static library
ADD_LIBRARY(OPGL_test_clion_static STATIC ${OPGL_test_clion_SRCS})
SET_TARGET_PROPERTIES(OPGL_test_clion_static PROPERTIES OUTPUT_NAME "OPGL_test_clion")
SET_TARGET_PROPERTIES(OPGL_test_clion PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OPGL_test_clion_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)