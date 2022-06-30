#ifndef CUBOID_H
#define CUBOID_H
#include "GameObject.h"
#include "GameObject/Interfaces/Collidable.h"
#include <memory>
#include <reactphysics3d/reactphysics3d.h>

class PositionNormals;
class Shader;
class Cuboid: public GameObject, public Collidable {
private:
    std::unique_ptr<PositionNormals> m_CubeGPUData;
    
    double m_Width;
    double m_Length;
    double m_Height;
public:
    Cuboid(const glm::vec3& position, double width, double height, double length);
    Cuboid(reactphysics3d::PhysicsWorld* world, const glm::vec3& position, double width, double height, double length);
    
    virtual void Render(Shader* shader) override;
    virtual void Update(double) override;
};
#endif
