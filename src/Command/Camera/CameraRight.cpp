#include "Command/Camera/CameraRight.h"
#include "Camera/Camera.h"

void CameraRight::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(Camera::Movement::RIGHT, deltaTime);
}

CameraRight::CameraRight(Camera* camera) : CameraCommand::CameraCommand(camera)
{
}
