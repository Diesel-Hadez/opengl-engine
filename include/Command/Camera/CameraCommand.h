#ifndef CAMERACOMMAND_H
#define CAMERACOMMAND_H
#include "Command/Command.h"

class Camera;
class CameraCommand: public Command {
protected:
    Camera* m_Camera;
public:
    CameraCommand(Camera* camera);
    virtual ~CameraCommand() = default;
};

#endif

