//
// Created by lvjiaming on 2018/11/27.
//

#include <sys/param.h>

#include <Macro.h>
#include <render/point/Point.h>
#include <Config.h>

Point::Point()
: _bufferCapacityGLPoint(0)
, _bufferCountGLPoint(0)
, _bufferGLPoint(nullptr)
, _dirty(false)
, _glProgram(nullptr)
{
    init();
}

Point::~Point() {
    free(_bufferGLPoint);
    _bufferGLPoint = nullptr;

    _bufferCapacityGLPoint = 0;
    _bufferCountGLPoint = 0;

    delete _glProgram;
}

void Point::init() {
    ensureCapacity(10);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4F)*_bufferCapacityGLPoint, _bufferGLPoint, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F), (void *)offsetof(V3F_C4F, vertices));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(V3F_C4F), (void *)offsetof(V3F_C4F, colors));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _glProgram = new Shader(point_vertexShaderSource, point_fragmentShaderSource, point_geometryShaderSource);


}

void Point::ensureCapacity(size_t count) {
    ASSERT(count >= 0, "capacity must be >= 0");
    if (_bufferCountGLPoint + count > _bufferCapacityGLPoint) {
        _bufferCapacityGLPoint += MAX(_bufferCapacityGLPoint, count);
        _bufferGLPoint = (V3F_C4F*)realloc(_bufferGLPoint, _bufferCapacityGLPoint * sizeof(V3F_C4F));
    }
}

const Shader* Point::getShader() {
    return _glProgram;
}

void Point::drawPoint(const Vec3F &position, const Color4F &color) {
    ensureCapacity(1);

    V3F_C4F *point = _bufferGLPoint + _bufferCountGLPoint;
    V3F_C4F a = {position, color};
    *point = a;

    _bufferCountGLPoint += 1;
    _dirty = true;

}

void Point::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {
    UNUSED_PARAM(viewPos);

    if (_dirty) {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3F_C4F)*_bufferCapacityGLPoint, _bufferGLPoint, GL_STATIC_DRAW);
        _dirty = false;
    }

    glBindVertexArray(_vao);
    _glProgram->use();
    _glProgram->setMat4("model", glm::mat4(1.0f));
    _glProgram->setMat4("view", view);
    _glProgram->setMat4("projection", projection);
    glDrawArrays(GL_POINTS, 0, _bufferCountGLPoint);


}