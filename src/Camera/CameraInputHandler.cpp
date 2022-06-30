#include "Camera/CameraInputHandler.h"
#include <GLFW/glfw3.h>
#include "Command/Camera/CameraUp.h"
#include "Command/Camera/CameraDown.h"
#include "Command/Camera/CameraLeft.h"
#include "Command/Camera/CameraRight.h"
#include "Command/Camera/CameraForward.h"
#include "Command/Camera/CameraBackward.h"
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

CameraInputHandler::CameraInputHandler(Scene* scene, FPCamera* camera): m_Camera(camera),
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
    
    m_CommandForward = new CameraForward(m_Camera);
    m_CommandBackward = new CameraBackward(m_Camera);
    m_CommandLeft = new CameraLeft(m_Camera);
    m_CommandRight = new CameraRight(m_Camera);
    m_CommandUp = new CameraUp(m_Camera);
    m_CommandDown = new CameraDown(m_Camera);
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
