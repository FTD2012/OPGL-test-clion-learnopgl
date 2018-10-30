//
// Created by lvjiaming on 2018/8/8.
//

#ifndef OPGL_TEST_CLION_LOADER_H
#define OPGL_TEST_CLION_LOADER_H

#include <string>
#include <vector>
#include <unordered_map>

#include <render/types/types.h>

class Loader {

public:
    static Loader *getInstance();

    Texture loadTexture(const std::string &path, TextureType textureType = TextureType::NONE);
    unsigned int loadCubeMapTexture(const std::vector<std::string> &path, TextureType textureType = TextureType::NONE);

private:

    Texture _loadTexture(const std::string &path, TextureType textureType);
    std::unordered_map<std::string, Texture> _textures;

};


#endif //OPGL_TEST_CLION_LOADER_H
