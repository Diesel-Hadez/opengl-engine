#include "Command/Camera/CameraRight.h"
#include "FPCamera.h"

void CameraRight::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(FPCamera::Movement::RIGHT, deltaTime);
}

CameraRight::CameraRight(FPCamera* camera) : CameraCommand::CameraCommand(camera)
{
}
