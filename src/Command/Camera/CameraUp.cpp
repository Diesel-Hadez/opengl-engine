#include "Command/Camera/CameraUp.h"
#include "FPCamera.h"

void CameraUp::execute(Scene* scene, float deltaTime) {
    m_Camera->ProcessKeyboard(FPCamera::Movement::UP, deltaTime);
}

CameraUp::CameraUp(FPCamera* camera) : CameraCommand::CameraCommand(camera)
{
}
