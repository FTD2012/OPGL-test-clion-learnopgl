//
// Created by lvjiaming on 2018/8/8.
//
#include <external/stb_image.h>
#include <external/glad.h>

#include "Loader.h"
#include "Macro.h"

using namespace std;
static Loader *s_ShaderLoader = nullptr;

Loader *Loader::getInstance() {
    if (!s_ShaderLoader) {
        s_ShaderLoader = new Loader();
        ASSERT(s_ShaderLoader, "FATAL: Not enough memory");
    }
    return s_ShaderLoader;
}


Texture Loader::loadTexture(const std::string &path, TextureType textureType) {
    ASSERT(!path.empty(), "Invalid texture path\n");

    auto it = _textures.find(path);
    if (it != _textures.end()) {
        return it->second;
    } else {
        return _loadTexture(path, textureType);
    }
}

Texture Loader::_loadTexture(const std::string &path, TextureType textureType) {
    // Image
    /* 使用'stb_image.h'的API把一张图片加载到内存中 */
    GLenum format = GL_RGBA;
    unsigned int texture;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    ASSERT(data, (std::string("Failed to load texture [") + path + "]\n").c_str());

    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    /* 使用一个独一无二的ID，生成一个纹理对象 */
    glGenTextures(1, &texture);
    /* 将texture绑定为2D纹理对象 */
    glBindTexture(GL_TEXTURE_2D, texture);

    /* 设置纹理的环绕模式为GL_REPEAT
     * GL_REPEAT: 对纹理的默认行为，重复纹理图像。
     * GL_MIRRORED_REPEAT: 和GL_REPEAT一样，但每次重复图片是镜像的。
     * GL_CLAMP_TO_EDGE: 纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
     * GL_CLAMP_TO_BORDER: 超出的坐标为用户指定的边缘颜色。
     * s => x
     * t => y
     * r => z
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* 设置纹理的过滤模式(进行放大和缩小操作时)为GL_LINEAR
     * GL_NEAREST: 临近过滤(Nearest Neighbor Filtering)，选择离中心店最近的纹理坐标的像素。
     * GL_LINEAR: 线性过滤((Bi)linear Filtering)，基于纹理坐标附近的纹理像素，计算出相应的插值，距离中心越近，权重越大。
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /* 将图片数据生成一个纹理 */
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    /* 生成多级渐远纹理(Mipmap) */
    glGenerateMipmap(GL_TEXTURE_2D);

    _textures.insert(std::make_pair(path, Texture{ texture, path, textureType }));
    stbi_image_free(data);
    return Texture{ texture, path, textureType };

}