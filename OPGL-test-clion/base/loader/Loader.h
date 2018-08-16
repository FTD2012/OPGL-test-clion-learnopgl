//
// Created by lvjiaming on 2018/8/8.
//

#ifndef OPGL_TEST_CLION_LOADER_H
#define OPGL_TEST_CLION_LOADER_H

#include <string>
#include <unordered_map>

class Loader {

public:
    static Loader *getInstance();

    unsigned int loadTexture(const std::string &path);

private:

    unsigned int _loadTexture(const std::string &path);
    std::unordered_map<std::string, unsigned int> _textures;

};


#endif //OPGL_TEST_CLION_LOADER_H
