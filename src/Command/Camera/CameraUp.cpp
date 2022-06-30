#include "Command/Camera/CameraUp.h"
#include "Camera/Camera.h"

void CameraUp::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(Camera::Movement::UP, deltaTime);
}

CameraUp::CameraUp(Camera* camera) : CameraCommand::CameraCommand(camera)
{
}
