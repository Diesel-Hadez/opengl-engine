#include "Shader.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Shader.h"
#include "assimp/material.h"
#include "assimp/types.h"

#include <stb_image.h>
#include <algorithm>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

namespace {
    unsigned int
    TextureFromFile(const char* path, const std::string& directory, bool gamma = false) {
        std::string filename = std::string(path);
        filename             = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int            width, height, nrComponents;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum format;
            if (nrComponents == 1) {
                format = GL_RED;
            } else if (nrComponents == 3) {
                format = GL_RGB;
            } else if (nrComponents == 4) {
                format = GL_RGBA;
            }
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         format,
                         width,
                         height,
                         0,
                         format,
                         GL_UNSIGNED_BYTE,
                         data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load texture " << filename << std::endl;
            stbi_image_free(data);
        }
        return textureID;
    }
}  // namespace

namespace Model {
    Model::Model(const std::string& path) { LoadModel(path); }

    void Model::Draw(Shader& shader) {
        for (auto& mesh : meshes) {
            mesh.Draw(shader);
        }
    }

    void Model::LoadModel(const std::string& path) {
        Assimp::Importer import;
        const aiScene*   scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode* node, const aiScene* scene) {
        // Process Node's meshes
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }

        // Process Children
        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }
    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {

        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;

            glm::vec3 vector;
            vector.x        = mesh->mVertices[i].x;
            vector.y        = mesh->mVertices[i].y;
            vector.z        = mesh->mVertices[i].z;
            vertex.Position = vector;

            vector.x      = mesh->mNormals[i].x;
            vector.y      = mesh->mNormals[i].y;
            vector.z      = mesh->mNormals[i].z;
            vertex.Normal = vector;

            if (mesh->mTextureCoords[0]) {
                glm::vec2 vec;
                vec.x            = mesh->mTextureCoords[0][i].x;
                vec.y            = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            } else {
                vertex.TexCoords = glm::vec2(0.f, 0.f);
            }

            vertices.push_back(vertex);
        }

        // Process Indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Process Materials
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial*          material = scene->mMaterials[mesh->mMaterialIndex];
            std::vector<Texture> diffuseMaps
                = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<Texture> specularMaps
                = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }
        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture>
    Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
            aiString str;
            mat->GetTexture(type, i, &str);

            bool skip = false;
            if (std::find_if(textures_loaded.begin(),
                             textures_loaded.end(),
                             [&str](const auto& a) {
                                 return std::string(a.path.data()) == std::string(str.C_Str());
                             })
                != textures_loaded.end()) {
                skip = true;
            }

            if (!skip) {
                Texture texture;
                std::cout << "Loading texture " << str.C_Str() << std::endl;
                texture.id = TextureFromFile(str.C_Str(), directory);
                std::cout << "Finished Loading texture " << str.C_Str() << std::endl;
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }

        return textures;
    }

}  // namespace Model
