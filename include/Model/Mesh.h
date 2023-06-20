#ifndef MESH_H
#define MESH_H
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Shader;

namespace Model {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture {
        unsigned int id;
        std::string  type;
        std::string  path;
    };

    class Mesh {
    private:
        unsigned int VAO, VBO, EBO;

        void SetupMesh();

    public:
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex>       vertices,
             std::vector<unsigned int> indices,
             std::vector<Texture>      textures);
        void Draw(Shader& shader);
    };
}  // namespace Model

#endif
