# CMakeLists for src directory
PROJECT(OPGL_test_clion)

SET(OPGL_test_clion_SRCS
        external
        external/khrplatform.h
        external/glad.h
        external/glad.c
        external/stb_image.h
        external/glm

        camera
        camera/Camera.h
        camera/camera.cpp

        light
        light/directionLight
        light/directionLight/DirectionLight.h
        light/directionLight/DirectionLight.cpp

        light/pointLight
        light/pointLight/PointLight.h
        light/pointLight/PointLight.cpp

        light/spotLight
        light/spotLight/SpotLight.h
        light/spotLight/SpotLight.cpp

        loader
        loader/Loader.h
        loader/Loader.cpp
        loader/Mesh.h
        loader/Mesh.cpp
        loader/Model.h
        loader/Model.cpp

        render
        render/cube
        render/cube/Cube.h
        render/cube/Cube.cpp

        render/scene
        render/scene/Scene.h
        render/scene/Scene.cpp

        render/sprite
        render/sprite/Sprite.h
        render/sprite/Sprite.cpp

        render/line
        render/line/Line.h
        render/line/Line.cpp

        render/object
        render/object/LightObject.h
        render/object/LightObject.cpp
        render/object/Object.h
        render/object/Object.cpp

        render/point
        render/point/Point.h
        render/point/Point.cpp

        render/types
        render/types/types.h
        render/types/Enums.h
        render/types/Enums.cpp

        Config.h
        Config.cpp
        Shader.h
        Shader.cpp
        Macro.h
        Constant.h
        Constant.cpp
        Global.h
        Global.cpp
        )

# shared library
ADD_LIBRARY(OPGL_test_clion SHARED ${OPGL_test_clion_SRCS})

# static library
ADD_LIBRARY(OPGL_test_clion_static STATIC ${OPGL_test_clion_SRCS})
SET_TARGET_PROPERTIES(OPGL_test_clion_static PROPERTIES OUTPUT_NAME "OPGL_test_clion")
SET_TARGET_PROPERTIES(OPGL_test_clion PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(OPGL_test_clion_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)