#include "Command/Camera/CameraBackward.h"
#include "Camera/Camera.h"

void CameraBackward::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(Camera::Movement::BACKWARD, deltaTime);
}

CameraBackward::CameraBackward(Camera* camera) : CameraCommand::CameraCommand(camera)
{
}
