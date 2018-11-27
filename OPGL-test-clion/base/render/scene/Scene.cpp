//
// Created by lvjiaming on 2018/8/17.
//

#include <render/scene/Scene.h>
#include <render/line/Line.h>
#include <Config.h>
#include <Macro.h>
#include <loader/Loader.h>
#include <Global.h>

Scene::Scene() {
    init();
}

Scene::~Scene() {

#ifdef ENABLE_FBO
    delete _sprite;
    _sprite = nullptr;
#endif

}

void Scene::enableCubeMap(bool isEnable) {
    if (_isEnableCubeMap != isEnable) {
        if (isEnable) {
            // load 6 cube maps
            _cubeMapTexture = Loader::getInstance()->loadCubeMapTexture(_textureFaces);
            skyboxTexture = _cubeMapTexture;

            glGenVertexArrays(1, &_cubeMapVao);
            glBindVertexArray(_cubeMapVao);

            glGenBuffers(1, &_cubeMapVbo);
            glBindBuffer(GL_ARRAY_BUFFER, _cubeMapVbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3F) * VERTICES_NUMBER, _bufferCubeMap, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3F), (void *)nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            _cubeMapGlProgram = new Shader(cube_map_vertexShaderSource, cube_map_fragmentShaderSource);

        } else {
            /// TODO: ljm >>> clear vertex、texture and shader
            skyboxTexture = 0;
        }

        _isEnableCubeMap = isEnable;
    }
}

void Scene::init() {

#ifdef ENABLE_FBO
    // 生成纹理附件
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // 生成渲染缓冲对象(Renderbuffer Object)附件
    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // 生成帧缓冲(Frame Buffer)
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    _sprite = new Sprite();
#endif

}


void Scene::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {

    // frame buffer
#ifdef ENABLE_FBO
    // first pass
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
#endif

    for (auto &it : _children) {
        it->onDraw(viewPos, view, projection);
    }

#ifdef ENABLE_FBO
    _sprite->setTexture(_texture);

    // second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    _sprite->onDraw();
#endif


    // sky box
    if (_isEnableCubeMap) {
        glDepthFunc(GL_LEQUAL);
        _cubeMapGlProgram->use();
        _cubeMapGlProgram->setMat4("view", glm::mat4(glm::mat3(view)));
        // _cubeMapGlProgram->setMat4("view", view);
        _cubeMapGlProgram->setMat4("projection", projection);
        glBindVertexArray(_cubeMapVao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTexture);
        glDrawArrays(GL_TRIANGLES, 0, VERTICES_NUMBER);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }

}

void Scene::drawWorld() {
    // line
    int worldWidth = 200;   // x
    int worldHeight = 200;  // y
    int worldDepth = 200;   // z
    auto *lineRender = new Line();
    lineRender->drawLine({0.0f,  0.0f, 0.0f}, {static_cast<float>(worldWidth), 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
    lineRender->drawLine({-1.0f * static_cast<float>(worldWidth),  0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    // lineRender->drawLine({0.0f,  0.0f, 0.0f}, {0.0f, static_cast<float>(worldHeight), 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f});
    // lineRender->drawLine({0.0f, -1.0f * static_cast<float>(worldHeight), 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    lineRender->drawLine({0.0f,  0.0f, 0.0f}, {0.0f, 0.0f, static_cast<float>(worldDepth)}, {0.0f, 0.0f, 1.0f, 1.0f});
    lineRender->drawLine({0.0f, 0.0f, -1.0f * static_cast<float>(worldDepth)}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f});

    // xz平面垂直于x轴的线
    for (int i = -1 * worldWidth; i <= worldWidth; i++) {
        if (i != 0.0f) {
            lineRender->drawLine({static_cast<float>(i), 0.0f, -1 * static_cast<float>(worldDepth)}, {static_cast<float>(i), 0.0f, static_cast<float>(worldDepth)}, {1.0f, 1.0f, 1.0f, 1.0f});
        }
    }
    // xz平面垂直于z轴的线
    for (int i = -1 * worldDepth; i <= worldDepth; i++) {
        if (i != 0.0f) {
            lineRender->drawLine({-1 * static_cast<float>(worldWidth), 0.0f, static_cast<float>(i)}, {static_cast<float>(worldWidth), 0.0f, static_cast<float>(i)}, {1.0f, 1.0f, 1.0f, 1.0f});
        }
    }
    addChild(lineRender);
}

void Scene::setFilter(const Filter &filter) {
#ifdef ENABLE_FBO
    _sprite->setFilter(filter);
#endif
}