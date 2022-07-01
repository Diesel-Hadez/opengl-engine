#include "Camera/CameraInputHandler.h"
#include <GLFW/glfw3.h>
#include "Command/CameraMovement.h"
#include "Game.h"

void CameraInputHandler::HandleInputs(float deltaTime) {
    if (glfwGetKey(Game::m_Window, m_KeyUp) == GLFW_PRESS)
        m_CommandUp->execute(m_Scene, deltaTime);
    if (glfwGetKey(Game::m_Window, m_KeyDown) == GLFW_PRESS)
        m_CommandDown->execute(m_Scene, deltaTime);
    if (glfwGetKey(Game::m_Window, m_KeyLeft) == GLFW_PRESS)
        m_CommandLeft->execute(m_Scene, deltaTime);
    if (glfwGetKey(Game::m_Window, m_KeyRight) == GLFW_PRESS)
        m_CommandRight->execute(m_Scene, deltaTime);
    if (glfwGetKey(Game::m_Window, m_KeyForward) == GLFW_PRESS)
        m_CommandForward->execute(m_Scene, deltaTime);
    if (glfwGetKey(Game::m_Window, m_KeyBackward) == GLFW_PRESS)
        m_CommandBackward->execute(m_Scene, deltaTime);
}

CameraInputHandler::CameraInputHandler(Scene* scene, Camera* camera): m_Camera(camera),
m_Scene(scene)
{
    // TO-DO:
    // Can load from configuration file in future.
    m_KeyForward = GLFW_KEY_W;
    m_KeyBackward = GLFW_KEY_S;
    m_KeyLeft = GLFW_KEY_A;
    m_KeyRight = GLFW_KEY_D;
    m_KeyUp = GLFW_KEY_Q;
    m_KeyDown = GLFW_KEY_E;
    
    m_CommandForward = new CameraCommand(m_Camera, Camera::Movement::FORWARD);
    m_CommandBackward = new CameraCommand(m_Camera, Camera::Movement::BACKWARD);
    m_CommandLeft = new CameraCommand(m_Camera, Camera::Movement::LEFT);
    m_CommandRight = new CameraCommand(m_Camera, Camera::Movement::RIGHT);
    m_CommandUp = new CameraCommand(m_Camera, Camera::Movement::UP);
    m_CommandDown = new CameraCommand(m_Camera, Camera::Movement::DOWN);
}

CameraInputHandler::~CameraInputHandler()
{
    delete m_CommandForward;
    delete m_CommandBackward;
    delete m_CommandLeft;
    delete m_CommandRight;
    delete m_CommandUp;
    delete m_CommandDown;
}
