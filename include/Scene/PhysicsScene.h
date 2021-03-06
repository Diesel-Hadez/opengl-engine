#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H

#include <memory>
#include <reactphysics3d/reactphysics3d.h>

#include "Scene.h"
class Shader;
class FPCamera;
class Cuboid;
class Plane;
class CameraInputHandler;
class PhysicsScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<CameraInputHandler> m_CameraInputHandler;
    std::unique_ptr<Plane> m_Plane;
    std::unique_ptr<Cuboid> m_Cuboid;
    float m_DeltaTime;
    
    reactphysics3d::PhysicsWorld* m_World;
    
    reactphysics3d::Vector3 m_PlanePosition;
    reactphysics3d::Quaternion m_PlaneOrientation;
    reactphysics3d::Transform m_PlaneTransform;
    
    reactphysics3d::RigidBody* m_PlaneBody; 
    
    const reactphysics3d::decimal timeStep = 1.0f / 60.0f;
public:
    virtual void Update() override;
    virtual void Render() override;
    virtual void OnPause() override;
    virtual void OnResume() override;
    PhysicsScene();
    ~PhysicsScene();
};

#endif

