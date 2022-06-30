#include "GameObject/Interfaces/Collidable.h"
#include "Game.h"
using namespace _Collidable;

Collidable::Collidable(r3d::PhysicsWorld* world, const r3d::Vector3& position, const r3d::Quaternion& orientation) :
m_CollidablePosition(position),
m_CollidableOrientation(orientation)
{
    m_CollidableBody = world->createRigidBody(r3d::Transform(m_CollidablePosition, m_CollidableOrientation));
}


void Collidable::AddBoxCollider(const r3d::Vector3& shape,
                    const r3d::Transform& transform){
    	
	// For boxes
	// The parameters are divided by 2, similar to how for a sphere you use a radius
	// instead of diameter, here we use the size from the origin to the side.
	r3d::BoxShape * boxShape = Game::m_PhysicsCommon->createBoxShape(r3d::Vector3(5.f, 0.5f, 5.f));
    
    m_CollidableBody->addCollider(boxShape, transform);
}
