#include "Game.h"
#include <reactphysics3d/reactphysics3d.h>
#include <iostream>

auto main(int argc, char* argv[]) -> int {
    using namespace reactphysics3d;
    PhysicsCommon physicsCommon;

    PhysicsWorld* world = physicsCommon.createPhysicsWorld();

    Vector3 position(0, 20, 0);

    Quaternion orientation = Quaternion::identity();

    Transform transform(position, orientation);

    RigidBody* body = world->createRigidBody(transform);

    const decimal timeStep = 1.0f / 60.0f;

    for (int i = 0; i < 20; i++) {
        world->update(timeStep);

        const Transform& transform = body->getTransform();
        const Vector3&   position  = transform.getPosition();

        std::cout << "Body Position: (" << position.x << ", " << position.y << ", " << position.z
                  << ")" << std::endl;
    }

    try {
        Game::GetInstance().Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    } catch (...) {
        std::cerr << "FATAL UNKNOWN ERROR HAS OCCURED!"
                  << "\n";
    }
    return 0;
}
