//
// Created by lvjiaming on 2018/8/20.
//

#ifndef OPGL_TEST_CLION_MESH_H
#define OPGL_TEST_CLION_MESH_H

#include <vector>

#include <render/types/types.h>
#include <Shader.h>
#include <render/object/LightObject.h>

class Mesh: public LightObject {

public:

    explicit Mesh(std::vector<MeshVertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);
    ~Mesh() override;

    bool init() override;
    void setMaterial(const std::string &diffusePath, const std::string &specularPath, const std::string &normalPath, float shininess = 32.0f);
    void enableVisibleNormal(bool isEnable);
    void onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) override;
    void onDrawNormal(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection);
protected:

    /**
     * 可视化法线
     */
    bool                      _isEnableVisibleNormal;
    Shader                   *_glNormalProgram;


    unsigned int              _normalTextureId;

    std::vector<MeshVertex>   _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture>      _textures;

};


#endif //OPGL_TEST_CLION_MESH_H
