#include "Command/CameraMovement.h"

CameraCommand::CameraCommand(Camera* camera, Camera::Movement movement) : m_Camera(camera),
m_Movement(movement)
{}

void CameraCommand::execute(Scene* scene, float deltaTime)
{
    m_Camera->ProcessKeyboard(m_Movement, deltaTime);    
}
