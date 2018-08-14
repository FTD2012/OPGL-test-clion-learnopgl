//
// Created by lvjiaming on 2018/8/13.
//

#include <sys/param.h>

#include <external/glad.h>
#include <Macro.h>
#include <render/Line/Line.h>
#include <Config.h>

const unsigned int Line::LINE_WIDTH = 2;

Line::Line(unsigned int lineWidth)
: _bufferCapacityGLLine(0)
, _bufferCountGLLine(0)
, _bufferGLLine(nullptr)
, _lineWidth(lineWidth)
, _dirty(false)
, _glProgram(nullptr)
{
    init();
}

Line::~Line() {
    free(_bufferGLLine);
    _bufferGLLine = nullptr;

    _bufferCapacityGLLine = 0;
    _bufferCountGLLine = 0;

    delete _glProgram;
}

void Line::init() {
    ensureCapacity(10);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4F_T2F)*_bufferCapacityGLLine, _bufferGLLine, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F_T2F), (void *)offsetof(V3F_C4F_T2F, vertices));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F_T2F), (void *)offsetof(V3F_C4F_T2F, colors));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F_T2F), (void *)offsetof(V3F_C4F_T2F, texCoords));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _glProgram = new Shader(line_vertexShaderSource, line_fragmentShaderSource);

}

void Line::drawLine(const Vec3F &origin, const Vec3F &destination, const Color4F &color) {
    ensureCapacity(2);

    V3F_C4F_T2F *point = _bufferGLLine + _bufferCountGLLine;

    V3F_C4F_T2F a = {origin, color, Tex2F{0.0f, 0.0f}};
    V3F_C4F_T2F b = {destination, color, Tex2F{0.0f, 0.0f}};

    *point = a;
    *(point + 1) = b;

    _bufferCountGLLine += 2;
    _dirty = true;
}

void Line::ensureCapacity(size_t count) {
    ASSERT(count >= 0, "capacity must be >= 0");
    if (_bufferCountGLLine + count > _bufferCapacityGLLine) {
        _bufferCapacityGLLine += MAX(_bufferCapacityGLLine, count);
        _bufferGLLine = (V3F_C4F_T2F*)realloc(_bufferGLLine, _bufferCapacityGLLine * sizeof(V3F_C4F_T2F));
    }
}
void Line::onDrawLine(const glm::mat4 &model, const glm::mat4 &view, const glm::mat4 &projection) {

    if (_dirty) {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4F_T2F)*_bufferCapacityGLLine, _bufferGLLine, GL_STATIC_DRAW);
        _dirty = false;
    }

    glBindVertexArray(_vao);
    _glProgram->use();
    _glProgram->setMat4("model", model);
    _glProgram->setMat4("view", view);
    _glProgram->setMat4("projection", projection);
    glDrawArrays(GL_LINES, 0, _bufferCountGLLine);

}
