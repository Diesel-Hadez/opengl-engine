#ifndef CAMERALEFT_H
#define CAMERALEFT_H
#include "Command/Camera/CameraCommand.h"

class CameraLeft: public CameraCommand {
public:
    void execute(Scene* scene, float deltaTime) override;
    
    CameraLeft(Camera* camera);
    ~CameraLeft() = default;
};

#endif

