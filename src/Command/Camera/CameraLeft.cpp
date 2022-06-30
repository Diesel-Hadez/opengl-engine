#include "Command/Camera/CameraLeft.h"
#include "FPCamera.h"

void CameraLeft::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(FPCamera::Movement::LEFT, deltaTime);
}

CameraLeft::CameraLeft(FPCamera* camera) : CameraCommand::CameraCommand(camera)
{
}
