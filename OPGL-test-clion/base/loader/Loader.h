//
// Created by lvjiaming on 2018/8/8.
//

#ifndef OPGL_TEST_CLION_LOADER_H
#define OPGL_TEST_CLION_LOADER_H


class Loader {

public:
    static Loader *getInstance();

    unsigned int loadTexture(char const *path);

};


#endif //OPGL_TEST_CLION_LOADER_H
