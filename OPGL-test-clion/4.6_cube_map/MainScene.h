//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_MAINSCENE_H
#define OPGL_TEST_CLION_MAINSCENE_H

#include <vector>

#include <render/scene/Scene.h>

class MainScene: public Scene {

public:
    MainScene();
    ~MainScene();
    void init();
    void onDraw(const Camera &camera);

private:
    std::vector<glm::vec3> vegetation = {
            glm::vec3(-1.5f, 0.5f, -0.48f),
            glm::vec3( 1.5f, 0.5f,  0.51f),
            glm::vec3( 0.0f, 0.5f,  0.7f),
            glm::vec3(-0.3f, 0.5f, -2.3f),
            glm::vec3( 0.5f, 0.5f, -0.6f)
    };
};

#endif //OPGL_TEST_CLION_MAINSCENE_H
