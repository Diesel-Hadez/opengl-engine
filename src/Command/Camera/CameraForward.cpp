#include "Command/Camera/CameraForward.h"
#include "FPCamera.h"

void CameraForward::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(FPCamera::Movement::FORWARD, deltaTime);
}

CameraForward::CameraForward(FPCamera* camera) : CameraCommand::CameraCommand(camera)
{
}
