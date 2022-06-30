#ifndef CAMERAUP_H
#define CAMERAUP_H
#include "Command/Camera/CameraCommand.h"

class CameraUp: public CameraCommand {
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraUp(Camera* camera);
    ~CameraUp() = default;
};

#endif

