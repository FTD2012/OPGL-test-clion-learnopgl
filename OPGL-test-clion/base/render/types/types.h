//
// Created by lvjiaming on 2018/8/13.
//

#ifndef OPGL_TEST_CLION_TYPES_H
#define OPGL_TEST_CLION_TYPES_H

#endif //OPGL_TEST_CLION_TYPES_H

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