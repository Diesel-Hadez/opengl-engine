#include "Command/Camera/CameraBackward.h"
#include "FPCamera.h"

void CameraBackward::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(FPCamera::Movement::BACKWARD, deltaTime);
}

CameraBackward::CameraBackward(FPCamera* camera) : CameraCommand::CameraCommand(camera)
{
}
