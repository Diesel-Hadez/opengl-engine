#include "Scene/PhysicsScene.h"
#include "Shader.h"
#include "Game.h"
#include "FPCamera.h"
#include "GameObject/Plane.h"
#include "GameObject/Cuboid.h"
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
		m_World->update(timeStep);
		const r3d::Transform& transform = m_CuboidBody->getTransform();
		const r3d::Vector3& position = transform.getPosition();
		std::cout << "X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
		m_Cuboid->Update(timeStep);
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
        m_Cuboid->Render(m_Shader.get());
}

PhysicsScene::PhysicsScene():
m_Shader(std::make_unique<Shader>("../resources/lightingDiffuse.vs","../resources/lightingDiffuse.fs")),
m_FPCamera(std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f))),
m_DeltaTime(0.0f),
m_Plane(std::make_unique<Plane>(glm::vec3(0.f, -4.f, 0.f), 10.f, 10.f)),
m_PlanePosition(0, 20, 0),
m_PlaneOrientation(r3d::Quaternion::identity()),
m_PlaneTransform(m_PlanePosition, m_PlaneOrientation),
m_Cuboid(std::make_unique<Cuboid>(glm::vec3(0,4,0), 0.1, 0.1,0.1)),
m_CuboidPosition(0, 20, 0),
m_CuboidOrientation(r3d::Quaternion::identity()),
m_CuboidTransform(m_CuboidPosition, m_CuboidOrientation)
{
    m_SceneName = "PhysicsScene";
	
	m_World = m_PhysicsCommon.createPhysicsWorld();
	m_PlaneTransform.setPosition(r3d::Vector3(0.f, -4.f, 0.f));
	m_CuboidTransform.setPosition(r3d::Vector3(0.f, 4.f, 0.f));
	
	// For plane
	r3d::BoxShape * boxShape = m_PhysicsCommon.createBoxShape(r3d::Vector3(10.f, 1.f, 10.f));
	// For cuboid
	r3d::BoxShape * boxShape2 = m_PhysicsCommon.createBoxShape(r3d::Vector3(0.1, 0.1, 0.1));
	
	// For both
	r3d::Transform transform = r3d::Transform::identity();
	
	m_PlaneBody = m_World->createRigidBody(m_PlaneTransform);
	m_CuboidBody = m_World->createRigidBody(m_CuboidTransform);
	
	m_PlaneBody->enableGravity(false);
	
	r3d::Collider* planeCollider = m_PlaneBody->addCollider(boxShape, transform);
	r3d::Collider* cuboidCollider = m_CuboidBody->addCollider(boxShape2, transform);
    
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

