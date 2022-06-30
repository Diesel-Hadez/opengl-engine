#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H

#include <memory>
#include <reactphysics3d/reactphysics3d.h>

#include "Scene.h"
class Shader;
class FPCamera;
class Cuboid;
class Plane;
class PhysicsScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<Plane> m_Plane;
    std::unique_ptr<Cuboid> m_Cuboid;
    float m_DeltaTime;
    
    reactphysics3d::PhysicsWorld* m_World;
    
    reactphysics3d::Vector3 m_PlanePosition;
    reactphysics3d::Quaternion m_PlaneOrientation;
    reactphysics3d::Transform m_PlaneTransform;
    
    
    reactphysics3d::Vector3 m_CuboidPosition;
    reactphysics3d::Quaternion m_CuboidOrientation;
    reactphysics3d::Transform m_CuboidTransform;
    
    reactphysics3d::RigidBody* m_PlaneBody; 
    reactphysics3d::RigidBody* m_CuboidBody; 
    
    const reactphysics3d::decimal timeStep = 1.0f / 60.0f;
public:
    virtual void Update() override;
    virtual void Render() override;
    PhysicsScene();
    ~PhysicsScene();
};

#endif

