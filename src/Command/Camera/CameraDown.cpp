#include "Command/Camera/CameraDown.h"
#include "Camera/Camera.h"

void CameraDown::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(Camera::Movement::DOWN, deltaTime);
}

CameraDown::CameraDown(Camera* camera) : CameraCommand::CameraCommand(camera)
{
}
