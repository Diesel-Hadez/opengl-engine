#ifndef CAMERADOWN_H
#define CAMERADOWN_H
#include "Command/Camera/CameraCommand.h"


class CameraDown: public CameraCommand {
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraDown(FPCamera* camera);
    ~CameraDown() = default;
};

#endif
