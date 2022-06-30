#ifndef CAMERACOMMAND_H
#define CAMERACOMMAND_H
#include "Command/Command.h"

class FPCamera;
class CameraCommand: public Command {
protected:
    FPCamera* m_Camera;
public:
    CameraCommand(FPCamera* camera);
    virtual ~CameraCommand() = default;
};

#endif

