//
// Created by lvjiaming on 2018/11/27.
//

#ifndef OPGL_TEST_CLION_POINT_H
#define OPGL_TEST_CLION_POINT_H


#include <render/object/Object.h>
#include <render/types/types.h>
#include <Shader.h>

class Point: public Object {

public:
    Point();
    ~Point() override;

    void init();
    const Shader *getShader();
    void drawPoint(const Vec3F &position, const Color4F &color);
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

private:

    void ensureCapacity(size_t count);

private:

    bool _dirty;

    /**
     * 总顶点数
     */
    GLsizei       _bufferCapacityGLPoint;

    /**
     * 已使用的顶点数
     */
    GLsizei      _bufferCountGLPoint;

    V3F_C4F     *_bufferGLPoint;

    Shader      *_glProgram;

    unsigned int _vao;
    unsigned int _vbo;


};


#endif //OPGL_TEST_CLION_POINT_H
