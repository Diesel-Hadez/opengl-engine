#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H
#include "Command/Command.h"
#include "Camera/Camera.h"

class CameraCommand: public Command {
protected:
    Camera* m_Camera;
    Camera::Movement m_Movement;
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraCommand(Camera* camera, Camera::Movement movement);
    ~CameraCommand() = default;
};

#endif

