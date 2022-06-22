#include "Scene/ColoursScene.h"
#include "Game.h"
#include "FPCamera.h"
#include "Shader.h"
#include "GPUData/Position.h"
#include "SampleVertices.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>


static ColoursScene *	curGameScene	= nullptr;

namespace {
    float currentFrame = 0;
    float lastFrame = 0;
    
    
    glm::vec3 cubePositions[] = {glm::vec3(2.0f, 2.0f, 2.0f),
                                 glm::vec3(2.0f, 5.0f, -15.0f),
                                 glm::vec3(-1.5f, -2.2f, -2.5f),
                                 glm::vec3(-3.8f, -2.0f, -12.3f),
                                 glm::vec3(2.4f, -0.4f, -3.5f),
                                 glm::vec3(-1.7f, 3.0f, -7.5f),
                                 glm::vec3(1.3f, -2.0f, -2.5f),
                                 glm::vec3(1.5f, 2.0f, -2.5f),
                                 glm::vec3(1.5f, 0.2f, -1.5f),
                                 glm::vec3(-1.3f, 1.0f, -1.5f)};
}
void ColoursScene::Update() {
	currentFrame   = glfwGetTime();
	m_DeltaTime    = currentFrame - lastFrame;
	lastFrame      = currentFrame;
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
	if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        this->m_End = true;
}

void ColoursScene::Render() {
    m_Shader->Use();
    
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Use();

        glm::mat4 view = glm::mat4(1.0f);

        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model      = glm::mat4(1.0f);
    
        projection           = glm::perspective(glm::radians(45.0f),
                                      (float)(WINDOW_WIDTH) / (float)(WINDOW_HEIGHT),
                                      0.1f,
                                      100.0f);
        view = m_FPCamera->GetViewMatrix();

        m_Shader->Set<glm::mat4>("projection", projection);
        m_Shader->Set<glm::mat4>("view", view);
        m_Shader->Set<glm::mat4>("model", model);
        
        m_Shader->Set<glm::vec3>("lightColor", glm::vec3(1.0f, 0.5f, 0.31f));
        m_Shader->Set<glm::vec3>("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));

        m_CubeGPUData->Bind();

        glDrawArrays(GL_TRIANGLES, 0, CubeVertices);
        
        
        m_LightCubeShader->Use();
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.5f));
        model = glm::scale(model, glm::vec3(0.3f));
        m_LightCubeShader->Set<glm::mat4>("model", model);
        m_LightCubeShader->Set<glm::mat4>("projection", projection);
        m_LightCubeShader->Set<glm::mat4>("view", view);
        m_LightGPUData->Bind();
        glDrawArrays(GL_TRIANGLES, 0, CubeVertices);
}

ColoursScene::ColoursScene():
m_Shader(std::make_unique<Shader>("../resources/lighting1.vs","../resources/lighting1.fs")),
m_LightCubeShader(std::make_unique<Shader>("../resources/lightingcube1.vs","../resources/lightingcube1.fs")),
m_FPCamera(std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f))),
m_DeltaTime(0.0f),
m_CubeGPUData(std::make_unique<Position>()),
m_LightGPUData(std::make_unique<Position>())
{
    m_SceneName = "ColoursScene";
    
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
    
 
    m_CubeGPUData->Prepare(const_cast<float*>(Cube), sizeof(Cube));
    m_LightGPUData->Prepare(const_cast<float*>(Cube), sizeof(Cube));
    
}

ColoursScene::~ColoursScene() {
    //Reset Callback
    glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{});
    
}
