#include "Command/Camera/CameraDown.h"
#include "FPCamera.h"

void CameraDown::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(FPCamera::Movement::DOWN, deltaTime);
}

CameraDown::CameraDown(FPCamera* camera) : CameraCommand::CameraCommand(camera)
{
}
