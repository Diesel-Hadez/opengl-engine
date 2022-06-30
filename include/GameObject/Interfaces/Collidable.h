#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <reactphysics3d/reactphysics3d.h>
namespace _Collidable{
    namespace r3d = reactphysics3d;
    class Collidable {
    protected:
        r3d::Vector3 m_CollidablePosition;
        r3d::Quaternion m_CollidableOrientation;
        
        r3d::RigidBody* m_CollidableBody;
        
        void AddBoxCollider(const r3d::Vector3& shape,
                            const r3d::Transform& transform= r3d::Transform::identity());
    public:
        Collidable(r3d::PhysicsWorld* world, const r3d::Vector3&, const r3d::Quaternion&);
        virtual ~Collidable() = default;
    };
}

using _Collidable::Collidable;

#endif
