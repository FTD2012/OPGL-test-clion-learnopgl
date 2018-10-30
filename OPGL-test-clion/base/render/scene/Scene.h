//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_SCENE_H
#define OPGL_TEST_CLION_SCENE_H


#include <render/object/Object.h>
#include <camera/Camera.h>
#include <render/sprite/Sprite.h>
#include <Constant.h>

#include <vector>

#define VERTICES_NUMBER (36)

class Scene: public Object {

public:
    Scene();
    ~Scene();
    void enableCubeMap(bool isEnable);
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;
    void drawWorld();
    void setFilter(const Filter &filter);

protected:
    void init();

    /**
     * 帧缓冲
     */
    unsigned int _fbo;
    unsigned int _texture;
    unsigned int _rbo;
    Sprite       *_sprite;

    /**
     * 是否开启立方体贴图
     */
    bool         _isEnableCubeMap;
    unsigned int _cubeMapTexture;
    unsigned int _cubeMapVao;
    unsigned int _cubeMapVbo;
    Shader       *_cubeMapGlProgram;
    std::vector<std::string> _textureFaces = {
        "../../texture/skybox/fix_right.jpg",
        "../../texture/skybox/fix_left.jpg",
        "../../texture/skybox/fix_top.jpg",
        "../../texture/skybox/fix_bottom.jpg",
        "../../texture/skybox/fix_front.jpg",
        "../../texture/skybox/fix_back.jpg",
    };
    Vec3F       _bufferCubeMap[VERTICES_NUMBER] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
    };

};


#endif //OPGL_TEST_CLION_SCENE_H
