#include "Command/Camera/CameraLeft.h"
#include "Camera/Camera.h"

void CameraLeft::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(Camera::Movement::LEFT, deltaTime);
}

CameraLeft::CameraLeft(Camera* camera) : CameraCommand::CameraCommand(camera)
{
}
