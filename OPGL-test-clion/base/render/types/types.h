//
// Created by lvjiaming on 2018/8/13.
//

#ifndef OPGL_TEST_CLION_TYPES_H
#define OPGL_TEST_CLION_TYPES_H

#include <string>

#include <external/glm/detail/type_mat.hpp>
#include <external/glm/glm.hpp>
#include <external/glm/gtc/matrix_transform.hpp>
#include <external/glm/gtc/type_ptr.hpp>

#include <render/types/Enums.h>

struct Vec2F {
    float u;
    float v;
};

struct Vec3F {
    float x;
    float y;
    float z;
};

struct Color4F {
    float r;
    float g;
    float b;
    float a;
};

struct Tex2F {
    float u;
    float v;
};

struct V3F_C4F_T2F {
    Vec3F   vertices;
    Color4F colors;
    Tex2F   texCoords;
};

struct V3F_N3F_T2F_C4F {
    Vec3F   vertices;
    Vec3F   normals;
    Tex2F   texCoords;
    Color4F colors;
};

struct MeshVertex {
    Vec3F   vertices;
    Vec3F   normals;
    Vec3F   tangent;    // 正切
    Vec3F   bitangent;  // 双切线的(from baidu)
    Tex2F   texCoords;
};

struct Texture {
    unsigned int textureId;
    std::string path;
    TextureType textureType;
};

#endif //OPGL_TEST_CLION_TYPES_H