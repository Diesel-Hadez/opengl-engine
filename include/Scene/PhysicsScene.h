#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H

#include <memory>
#include <reactphysics3d/reactphysics3d.h>

#include "Scene.h"
class Shader;
class FPCamera;
class Cuboid;
class Plane;
namespace _PhysicsScene {
    namespace r3d = reactphysics3d;
    class PhysicsScene: public Scene {
    private:
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<FPCamera> m_FPCamera;
        std::unique_ptr<Plane> m_Plane;
        std::unique_ptr<Cuboid> m_Cuboid;
        float m_DeltaTime;
        
        r3d::PhysicsWorld* m_World;
        
        r3d::Vector3 m_PlanePosition;
        r3d::Quaternion m_PlaneOrientation;
        r3d::Transform m_PlaneTransform;
        
        
        r3d::Vector3 m_CuboidPosition;
        r3d::Quaternion m_CuboidOrientation;
        r3d::Transform m_CuboidTransform;
        
        r3d::RigidBody* m_PlaneBody; 
        r3d::RigidBody* m_CuboidBody; 
        
        const r3d::decimal timeStep = 1.0f / 60.0f;
    public:
        virtual void Update() override;
        virtual void Render() override;
        PhysicsScene();
        ~PhysicsScene();
    };
}
using _PhysicsScene::PhysicsScene;

#endif

