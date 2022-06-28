#include "Scene/PhysicsScene.h"
#include "Shader.h"
#include "Game.h"
#include "FPCamera.h"
#include "GameObject/Plane.h"
#include "GPUData/PositionNormals.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>


static PhysicsScene *	curGameScene	= nullptr;

namespace {
    float currentFrame = 0;
    float lastFrame = 0;
    
}
void PhysicsScene::Update() {
	constexpr double timeStep = 1.0 / 60.0;
	double accumulator {0.0};
	currentFrame   = glfwGetTime();
	m_DeltaTime    = currentFrame - lastFrame;
	lastFrame      = currentFrame;
	accumulator += m_DeltaTime;
	
	while (accumulator >= timeStep) {
		if (glfwGetKey(Game::m_Window, GLFW_KEY_W) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::FORWARD, timeStep);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::BACKWARD, timeStep);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_A) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::LEFT, timeStep);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::RIGHT, timeStep);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_Q) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::UP, timeStep);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_E) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::DOWN, timeStep);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			this->m_End = true;
		
		accumulator -= timeStep;
	}
}

void PhysicsScene::Render() {
    m_Shader->Use();
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Use();

        glm::mat4 view = glm::mat4(1.0f);

        glm::mat4 projection = glm::mat4(1.0f);
        projection           = glm::perspective(glm::radians(45.0f),
                                      (float)(WINDOW_WIDTH) / (float)(WINDOW_HEIGHT),
                                      0.1f,
                                      100.0f);
        view = m_FPCamera->GetViewMatrix();

        m_Shader->Set<glm::mat4>("projection", projection);
        m_Shader->Set<glm::mat4>("view", view);
        
        m_Plane->Render(m_Shader.get());
}

PhysicsScene::PhysicsScene():
m_Shader(std::make_unique<Shader>("../resources/lightingDiffuse.vs","../resources/lightingDiffuse.fs")),
m_FPCamera(std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f))),
m_DeltaTime(0.0f),
m_Plane(std::make_unique<Plane>(glm::vec3(1.f), 10.f, 10.f)),
m_Position(0, 20, 0),
m_Orientation(r3d::Quaternion::identity()),
m_Transform(m_Position, m_Orientation)
{
    m_SceneName = "PhysicsScene";
	
	m_World = m_PhysicsCommon.createPhysicsWorld();
	m_Body = m_World->createRigidBody(m_Transform);
    
	//Dirty Hack for callbacks
	curGameScene = this;

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
		curGameScene->m_FPCamera->ProcessMouseMovement(xOffset, yOffset);
	});
	glfwSetScrollCallback(Game::m_Window, [](GLFWwindow * window, double xOffset, double yOffset) {
		curGameScene->m_FPCamera->ProcessMouseScroll(yOffset);
	});

}

PhysicsScene::~PhysicsScene() {
    //Reset Callback
    glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{});
    
}
