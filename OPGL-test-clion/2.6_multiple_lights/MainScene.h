//
// Created by lvjiaming on 2018/8/17.
//

#ifndef OPGL_TEST_CLION_MAINSCENE_H
#define OPGL_TEST_CLION_MAINSCENE_H

#include <render/scene/Scene.h>

class MainScene: public Scene {

public:
    MainScene();
    ~MainScene();
    void init();
    void onDraw(const Camera &camera);



};




#endif //OPGL_TEST_CLION_MAINSCENE_H
