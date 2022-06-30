#ifndef CAMERABACKWARD_H
#define CAMERABACKWARD_H
#include "Command/Camera/CameraCommand.h"


class CameraBackward: public CameraCommand {
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraBackward(FPCamera* camera);
    ~CameraBackward() = default;
};

#endif

