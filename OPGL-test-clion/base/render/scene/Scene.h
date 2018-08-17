//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_SCENE_H
#define OPGL_TEST_CLION_SCENE_H


#include <render/object/Object.h>
#include <camera/Camera.h>

class Scene: public Object {
public:
    Scene();
    ~Scene();
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

private:


};


#endif //OPGL_TEST_CLION_SCENE_H
