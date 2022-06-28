#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

class Shader;
class GameObject {
protected:
    glm::vec3 m_Position;
public:
    GameObject() = default;
    GameObject(glm::vec3 position) {m_Position = position;}
    virtual ~GameObject() = default;
    virtual void Render(Shader*)=0;
    virtual void Update(double)=0;
};

#endif
