#ifndef CAMERARIGHT_H
#define CAMERARIGHT_H
#include "Command/Camera/CameraCommand.h"

class CameraRight: public CameraCommand {
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraRight(Camera* camera);
    ~CameraRight() = default;
};

#endif

