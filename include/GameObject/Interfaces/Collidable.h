#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <reactphysics3d/reactphysics3d.h>

class Collidable {
protected:
    bool m_PhysicsWorldExists;
    
    reactphysics3d::Vector3 m_CollidablePosition;
    reactphysics3d::Quaternion m_CollidableOrientation;
    
    reactphysics3d::RigidBody* m_CollidableBody;
    
    void AddBoxCollider(const reactphysics3d::Vector3& shape,
                        const reactphysics3d::Transform& transform= reactphysics3d::Transform::identity());
public:
    void SetGravity(bool enable);
    void SetType(reactphysics3d::BodyType type);
public:
    Collidable(reactphysics3d::PhysicsWorld* world, const reactphysics3d::Vector3&, const reactphysics3d::Quaternion&);
    Collidable();
    virtual ~Collidable() = default;
};

#endif
