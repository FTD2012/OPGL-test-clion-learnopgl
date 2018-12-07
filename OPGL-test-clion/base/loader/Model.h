//
// Created by lvjiaming on 2018/8/20.
//

#ifndef OPGL_TEST_CLION_MODEL_H
#define OPGL_TEST_CLION_MODEL_H

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <loader/Mesh.h>
#include <render/object/Object.h>

class Model: public Object {
public:
    explicit Model(const char *path);

    void addDirectionLight(const DirectionLight *directionLight);
    void addPointLight(const PointLight *pointLight);
    void enableInstancing(bool isEnable, std::vector<glm::mat4> modelMatrices);
    void enableVisibleNormal(bool isEnable);
    void setPosition(const glm::vec3 &position) override;
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;

private:
    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);
    Mesh *processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadTexture(aiMaterial *material, aiTextureType type, TextureType textureType);


private:

    /**
     * 实例化
     */
    bool _isEnableInstancing;
    unsigned int _instancingVbo;

    /**
     * 可视化发现
     */
    bool _isEnableVisibleNormal;
    std::vector<Mesh*> _meshes;
    const aiScene *_scene;
    std::string _directory;


    
};


#endif //OPGL_TEST_CLION_MODEL_H
