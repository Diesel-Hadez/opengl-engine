#include "Camera/FPCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
#include "Game.h"

const float FPCamera::YAW         = -90.0f;
const float FPCamera::PITCH       = 0.0f;
const float FPCamera::SPEED       = 2.5f;
const float FPCamera::SENSITIVITY = 0.1f;
const float FPCamera::ZOOM        = 45.0f;

static FPCamera * curFPCamera = nullptr;

void FPCamera::OnPause(){
    //Reset Callback
    glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{});
	glfwSetScrollCallback(Game::m_Window, [](GLFWwindow * window, double xOffset, double yOffset) {});
	glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void FPCamera::OnResume(){
    curFPCamera = this;

	glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{
		static bool firstMouse = true;
		static double lastX = static_cast<double>(WINDOW_WIDTH / 2.f), lastY = static_cast<double>(WINDOW_HEIGHT / 2.f);
		if (firstMouse)
		{
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}
		double xOffset = xPos - lastX;
		double yOffset = lastY - yPos;
		lastX = xPos;
		lastY = yPos;
		curFPCamera->ProcessMouseMovement(xOffset, yOffset);
	});
	glfwSetScrollCallback(Game::m_Window, [](GLFWwindow * window, double xOffset, double yOffset) {
		curFPCamera->ProcessMouseScroll(yOffset);
	});
}

void FPCamera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) noexcept {
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    UpdateCameraVectors();
}
void FPCamera::ProcessMouseScroll(float yOffset) noexcept {
    if (Zoom >= 1.0f && Zoom <= 45.0f)
        Zoom -= yOffset;
    if (Zoom <= 1.0f)
        Zoom = 1.0f;
    if (Zoom >= 45.0f)
        Zoom = 45.0f;
}

void FPCamera::ProcessKeyboard(Camera::Movement direction, float deltaTime) {
    using Movement = Camera::Movement;
    float velocity = MovementSpeed * deltaTime;
    if (direction == Movement::FORWARD)
        Position += Front * velocity;
    else if (direction == Movement::BACKWARD)
        Position -= Front * velocity;
    else if (direction == Movement::LEFT)
        Position -= Right * velocity;
    else if (direction == Movement::RIGHT)
        Position += Right * velocity;
    else if (direction == Movement::UP)
        Position += WorldUp * velocity;
    else if (direction == Movement::DOWN)
        Position -= WorldUp * velocity;
}

glm::mat4 FPCamera::GetViewMatrix() const noexcept {
    return glm::lookAt(Position, Position + Front, Up);
}


void FPCamera::UpdateCameraVectors() noexcept {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front   = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}

FPCamera::FPCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f))
    , MovementSpeed(SPEED)
    , MouseSensitivity(SENSITIVITY)
    , Zoom(ZOOM)
    , Position(position)
    , WorldUp(up)
    , Yaw(yaw)
    , Pitch(pitch) {
    UpdateCameraVectors();
    
    this->OnResume();
}

FPCamera::~FPCamera() {
    this->OnPause();
}
