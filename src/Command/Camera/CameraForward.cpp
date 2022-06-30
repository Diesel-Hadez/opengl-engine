#include "Command/Camera/CameraForward.h"
#include "Camera/Camera.h"

void CameraForward::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(Camera::Movement::FORWARD, deltaTime);
}

CameraForward::CameraForward(Camera* camera) : CameraCommand::CameraCommand(camera)
{
}
