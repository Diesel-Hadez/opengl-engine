#ifndef CAMERAFORWARD_H
#define CAMERAFORWARD_H
#include "Command/Camera/CameraCommand.h"


class CameraForward: public CameraCommand {
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraForward(FPCamera* camera);
    ~CameraForward() = default;
};

#endif
