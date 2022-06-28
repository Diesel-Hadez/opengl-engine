#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Shader;
class GameObject {
protected:
    glm::vec3 m_Position;
    glm::quat m_Rotation;
public:
    GameObject(): m_Position(0.0), m_Rotation(1, 0, 0, 0) {};
    GameObject(glm::vec3 position) {m_Position = position;}
    glm::vec3 GetPosition() const noexcept {return m_Position;}
    void SetPosition(glm::vec3 position) { m_Position = position;}
    
    glm::quat GetRotation() const noexcept {return m_Rotation;}
    void SetRotation(glm::quat rotation) { m_Rotation = rotation;}
    virtual ~GameObject() = default;
    virtual void Render(Shader*)=0;
    virtual void Update(double)=0;
};

#endif
