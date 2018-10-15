//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_SCENE_H
#define OPGL_TEST_CLION_SCENE_H


#include <render/object/Object.h>
#include <camera/Camera.h>
#include <render/sprite/Sprite.h>
#include <Constant.h>

class Scene: public Object {

public:
    Scene();
    ~Scene();
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;
    void drawWorld();
    void setFilter(const Filter &filter);

protected:
    void init();
    unsigned int _fbo;
    unsigned int _texture;
    unsigned int _rbo;

    Sprite       *_sprite;

};


#endif //OPGL_TEST_CLION_SCENE_H
