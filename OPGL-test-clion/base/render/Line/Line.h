//
// Created by lvjiaming on 2018/8/13.
//

#ifndef OPGL_TEST_CLION_LINE_H
#define OPGL_TEST_CLION_LINE_H

#include <cstddef>

#include <render/types/types.h>
#include <Shader.h>
#include <render/object/Object.h>

class Line: public Object {
public:

    explicit Line(unsigned int lineWidth = LINE_WIDTH);
    ~Line() override;

    void drawLine(const Vec3F &origin, const Vec3F &destination, const Color4F &color);

    void init();

    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

private:

    void ensureCapacity(size_t count);

private:

    bool         _dirty;

    /**
     * 线的宽度
     */
    unsigned int  _lineWidth;

    /**
     * 总计顶点数
     */
    GLsizei       _bufferCapacityGLLine;

    /**
     * 已使用的顶点数
     */
    GLsizei       _bufferCountGLLine;

    V3F_C4F_T2F  *_bufferGLLine;

    Shader       *_glProgram;

    unsigned int  _vao;
    unsigned int  _vbo;


protected:

    static const unsigned int LINE_WIDTH;

};

#endif //OPGL_TEST_CLION_LINE_H