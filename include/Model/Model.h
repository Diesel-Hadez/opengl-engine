#ifndef MODEL_H
#define MODEL_H
#include <string>
#include "Mesh.h"
#include "assimp/material.h"
#include <assimp/scene.h>

class Shader;
namespace Model {

    class Model {
    private:
        std::vector<Mesh>    meshes;
        std::vector<Texture> textures_loaded;
        std::string          directory;
        void                 LoadModel(const std::string& path);
        void                 ProcessNode(aiNode* node, const aiScene* scene);
        Mesh                 ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture>
        LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

    public:
        Model(const std::string& path);
        void Draw(Shader& shader);
    };
}  // namespace Model

#endif
