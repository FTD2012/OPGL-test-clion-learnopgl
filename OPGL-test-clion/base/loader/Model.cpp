//
// Created by lvjiaming on 2018/8/20.
//

#include <external/glm/vec3.hpp>

#include <loader/Mesh.h>
#include <loader/Model.h>
#include <Macro.h>
#include <render/types/types.h>
#include "Loader.h"

Model::Model(const char *path)
: _isEnableVisibleNormal(false)
, _isEnableInstancing(false)
{
    loadModel(std::string(path));
}

void Model::loadModel(std::string path) {
    Assimp::Importer importer;
    _scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    ASSERT(_scene && !(_scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE) && _scene->mRootNode, (std::string("ERROR::ASSIMP::") + importer.GetErrorString()).c_str());

    _directory = path.substr(0, path.find_last_of('/'));

    processNode(_scene->mRootNode, _scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
//    if (_meshes.size() >= 2) {
//        return;
//    }

    for (size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh, scene));
    }

    for (size_t i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh *Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<MeshVertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // mesh's vertices
    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(
            MeshVertex {
                Vec3F{ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z },
                Vec3F{ mesh->mNormals[i].x,  mesh->mNormals[i].y,  mesh->mNormals[i].z  },
                mesh->mTangents         ? Vec3F{ mesh->mTangents[i].x,   mesh->mTangents[i].y,   mesh->mTangents[i].z   } : Vec3F{ 0.0f, 0.0f, 0.0f },
                mesh->mBitangents       ? Vec3F{ mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z } : Vec3F{ 0.0f, 0.0f, 0.0f },
                mesh->mTextureCoords[0] ? Tex2F{ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y } : Tex2F{ 0.0f, 0.0f }
            }
        );
    }

    // mesh's face
    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // mesh's material
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps  = loadTexture(material, aiTextureType_DIFFUSE,  TextureType::DIFFUSE);
    std::vector<Texture> specularMaps = loadTexture(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
    std::vector<Texture> normalMaps   = loadTexture(material, aiTextureType_HEIGHT,   TextureType::NORMALS);   /// TODO: ljm >>> ensure this
    std::vector<Texture> heightMaps   = loadTexture(material, aiTextureType_AMBIENT,  TextureType::HEIGHT);    /// TODO: ljm >>> ensure this
    textures.insert(textures.end(), diffuseMaps.begin(),  diffuseMaps.end());
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    textures.insert(textures.end(), normalMaps.begin(),   normalMaps.end());
    textures.insert(textures.end(), heightMaps.begin(),   heightMaps.end());

    return new Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadTexture(aiMaterial *material, aiTextureType type, TextureType textureType) {
    aiString path;
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        material->GetTexture(type, i, &path);
        textures.push_back(Loader::getInstance()->loadTexture(path.C_Str(), textureType));
    }
    return textures;
}

void Model::addDirectionLight(const DirectionLight *directionLight) {
    for (auto &it : _meshes) {
        it->addDirectionLight(directionLight);
    }
}

void Model::addPointLight(const PointLight *pointLight) {
    for (auto &it : _meshes) {
        it->addPointLight(pointLight);
    }
}

void Model::enableInstancing(bool isEnable, std::vector<glm::mat4> modelMatrices) {
    if (_isEnableInstancing == isEnable) {
        return;
    }

    if (isEnable) {
        glGenBuffers(1, &_instancingVbo);
        glBindBuffer(GL_ARRAY_BUFFER, _instancingVbo);
        glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

        for (auto &it : _meshes) {
            it->enableInstancing(true, modelMatrices.size());
            it->bindInstancingBuffer();
        }

//        glBindBuffer(GL_ARRAY_BUFFER, 0);

    } else {
        // TODO: ljm >>> remove vertex
        for (auto &it : _meshes) {
            it->enableInstancing(false, 0);
        }
    }

}

void Model::enableVisibleNormal(bool isEnable) {
    if (_isEnableVisibleNormal == isEnable) {
        return;
    }
    _isEnableVisibleNormal = isEnable;

    for (auto &it : _meshes) {
        it->enableVisibleNormal(isEnable);
    }

}

void Model::setPosition(const glm::vec3 &position) {
    for (auto &it : _meshes) {
        it->setPosition(position);
    }
}

void Model::onDraw(const glm::vec3 &viewPos, const glm::mat4 &view, const glm::mat4 &projection) {
    for (auto &it : _meshes) {
        it->onDraw(viewPos, view, projection);
    }

    if (_isEnableVisibleNormal) {
        for (auto &it : _meshes) {
            it->onDrawNormal(viewPos, view, projection);
        }
    }

}


