#include "GameObject/Interfaces/Collidable.h"
#include "Game.h"

namespace r3d = reactphysics3d;

Collidable::Collidable(r3d::PhysicsWorld* world, const r3d::Vector3& position, const r3d::Quaternion& orientation) :
m_PhysicsWorldExists(true),
m_CollidablePosition(position),
m_CollidableOrientation(orientation)
{
    m_CollidableBody = world->createRigidBody(r3d::Transform(m_CollidablePosition, m_CollidableOrientation));
}

Collidable::Collidable(): m_PhysicsWorldExists(false){
}


void Collidable::SetGravity(bool enable) {
    m_CollidableBody->enableGravity(enable);
}

void Collidable::SetType(r3d::BodyType type) {
    m_CollidableBody->setType(type);
}


void Collidable::AddBoxCollider(const r3d::Vector3& shape,
                    const r3d::Transform& transform){
	// For boxes
	// The parameters are divided by 2, similar to how for a sphere you use a radius
	// instead of diameter, here we use the size from the origin to the side.
	r3d::BoxShape * boxShape = Game::m_PhysicsCommon->createBoxShape(shape * 0.5f);
    
    m_CollidableBody->addCollider(boxShape, transform);
}
