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

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
namespace {
    float currentFrame = 0;
    float lastFrame = 0;
	
	auto cursorMode = GLFW_CURSOR_DISABLED;
	auto tabPressed = false;
}
	
	
using namespace _PhysicsScene;

void PhysicsScene::Update() {
	constexpr double timeStep = 1.0 / 120.0;
	double accumulator {0.0};
	currentFrame   = glfwGetTime();
	m_DeltaTime    = currentFrame - lastFrame;
	lastFrame      = currentFrame;
	accumulator += m_DeltaTime;
	
	if (glfwGetKey(Game::m_Window, GLFW_KEY_W) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::FORWARD, m_DeltaTime);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::BACKWARD, m_DeltaTime);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_A) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::LEFT, m_DeltaTime);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::RIGHT, m_DeltaTime);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_Q) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::UP, m_DeltaTime);
		if (glfwGetKey(Game::m_Window, GLFW_KEY_E) == GLFW_PRESS)
			m_FPCamera->ProcessKeyboard(FPCamera::Movement::DOWN, m_DeltaTime);
		
		if (glfwGetKey(Game::m_Window, GLFW_KEY_I) == GLFW_PRESS)
			m_CuboidBody->applyWorldForceAtCenterOfMass(r3d::Vector3(10,0,0));
		if (glfwGetKey(Game::m_Window, GLFW_KEY_K) == GLFW_PRESS)
			m_CuboidBody->applyWorldForceAtCenterOfMass(r3d::Vector3(-10,0,0));
		if (glfwGetKey(Game::m_Window, GLFW_KEY_L) == GLFW_PRESS)
			m_CuboidBody->applyWorldForceAtCenterOfMass(r3d::Vector3(0,0,10));
		if (glfwGetKey(Game::m_Window, GLFW_KEY_J) == GLFW_PRESS)
			m_CuboidBody->applyWorldForceAtCenterOfMass(r3d::Vector3(0,0,-10));
		if (glfwGetKey(Game::m_Window, GLFW_KEY_U) == GLFW_PRESS)
			m_CuboidBody->applyWorldForceAtCenterOfMass(r3d::Vector3(0,50,0));
		if (glfwGetKey(Game::m_Window, GLFW_KEY_O) == GLFW_PRESS)
			m_CuboidBody->applyWorldForceAtCenterOfMass(r3d::Vector3(0,-50,0));
		if (glfwGetKey(Game::m_Window, GLFW_KEY_TAB) == GLFW_PRESS) {
			tabPressed = true;
		}
		if (tabPressed && glfwGetKey(Game::m_Window, GLFW_KEY_TAB) == GLFW_RELEASE) {
			tabPressed = false;
			
			if (cursorMode == GLFW_CURSOR_DISABLED) {
				cursorMode = GLFW_CURSOR_NORMAL;
			}
			else {
					cursorMode = GLFW_CURSOR_DISABLED;
			}
			
			glfwSetInputMode(Game::m_Window, GLFW_CURSOR, cursorMode);
		}
		if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			this->m_End = true;
		
	
	while (accumulator >= timeStep) {
		m_World->update(timeStep);
		m_Cuboid->Update(timeStep);
		
		accumulator -= timeStep;
	}
	{
		ImGui::Begin("Properties");
		{
			const r3d::Transform& transform = m_CuboidBody->getTransform();
			const r3d::Vector3& cubePosition = transform.getPosition();
			const r3d::Quaternion& cubeRotation = transform.getOrientation();
			
			ImGui::Text("Cube Position: (%f, %f, %f)",
						cubePosition.x,
						cubePosition.y,
						cubePosition.z);
			
			ImGui::Text("Cube Rotation: (%f, %f, %f, %f)",
						cubeRotation.x,
						cubeRotation.y,
						cubeRotation.z,
						cubeRotation.w);
			
			m_Cuboid->SetPosition(glm::vec3(cubePosition.x, cubePosition.y, cubePosition.z));
			m_Cuboid->SetRotation(glm::quat(cubeRotation.x, cubeRotation.y, cubeRotation.z, cubeRotation.w));
			
			
		}
		{
			const glm::vec3 cameraPos = m_FPCamera->Position;
			
			ImGui::Text("Camera Position: (%f, %f, %f)",
						cameraPos.x,
						cameraPos.y,
						cameraPos.z);
		}
		ImGui::End();
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
m_PlanePosition(0, -4, 0),
m_PlaneOrientation(r3d::Quaternion::identity()),
m_PlaneTransform(m_PlanePosition, m_PlaneOrientation),
m_Cuboid(std::make_unique<Cuboid>(glm::vec3(0.f,4.f,0.f), 0.1f, 0.1f,0.1f)),
m_CuboidPosition(0, 4, 0),
m_CuboidOrientation(r3d::Quaternion::identity()),
m_CuboidTransform(m_CuboidPosition, m_CuboidOrientation)
{
    m_SceneName = "PhysicsScene";
	
	m_World = Game::m_PhysicsCommon->createPhysicsWorld();
	
	
	// For plane
	// The parameters are divided by 2, similar to how for a sphere you use a radius
	// instead of diameter, here we use the size from the origin to the side.
	r3d::BoxShape * boxShape = Game::m_PhysicsCommon->createBoxShape(r3d::Vector3(5.f, 0.5f, 5.f));
	// For cuboid
	r3d::BoxShape * boxShape2 = Game::m_PhysicsCommon->createBoxShape(r3d::Vector3(0.05f, 0.05f, 0.05f));
	
	// For both
	r3d::Transform transform = r3d::Transform::identity();
	
	m_PlaneBody = m_World->createRigidBody(m_PlaneTransform);
	m_CuboidBody = m_World->createRigidBody(m_CuboidTransform);
	
	m_PlaneBody->enableGravity(false);
	
	r3d::Collider* planeCollider = m_PlaneBody->addCollider(boxShape, transform);
	r3d::Collider* cuboidCollider = m_CuboidBody->addCollider(boxShape2, transform);
    
	m_PlaneBody->enableGravity(false);
	m_PlaneBody->setType(r3d::BodyType::STATIC);
}

PhysicsScene::~PhysicsScene() {
}

