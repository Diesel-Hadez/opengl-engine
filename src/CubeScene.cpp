#include "CubeScene.h"
#include "Shader.h"
#include "Game.h"
#include "FPCamera.h"
#include "PositionTexture.h"
#include "Texture.h"
#include "SampleVertices.h"

#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>


static CubeScene *	curGameScene	= nullptr;

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
void CubeScene::Update() {
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

void CubeScene::Render() {
    m_Shader->Use();
    m_Shader->Set<int>("texture1", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Use();

        glm::mat4 view = glm::mat4(1.0f);

        constexpr float radius = 10.0f;

        float camX = sin(glfwGetTime()) * radius;
        float camY = cos(glfwGetTime()) * radius;

        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 model      = glm::mat4(1.0f);
        model                = glm::rotate(model,
                            (float)glfwGetTime() * glm::radians(50.0f),
                            glm::vec3(0.5f, 1.0f, 0.0f));
        projection           = glm::perspective(glm::radians(45.0f),
                                      (float)(WINDOW_WIDTH) / (float)(WINDOW_HEIGHT),
                                      0.1f,
                                      100.0f);
        // view                 = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // view = glm::lookAt(glm::vec3(camX, 0.00, camY), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        view = m_FPCamera->GetViewMatrix();

        m_Shader->Set<glm::mat4>("projection", projection);
        m_Shader->Set<glm::mat4>("view", view);
        m_Shader->Set<glm::mat4>("model", model);

        m_CubeGPUData->Bind();

        glDrawArrays(GL_TRIANGLES, 0, TexturedCubeVertices);

        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model           = glm::translate(model, cubePositions[i]);

            float angle = 20.0f * i;
            model       = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->Set<glm::mat4>("model", model);

            glDrawArrays(GL_TRIANGLES, 0, TexturedCubeVertices);
        }
}

CubeScene::CubeScene():
m_Shader(std::make_unique<Shader>("../resources/cubescene.vs","../resources/cubescene.fs")),
m_FPCamera(std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f))),
m_DeltaTime(0.0f),
m_CubeGPUData(std::make_unique<PositionTexture>()),
m_CubeTexture(std::make_unique<Texture>("../resources/image.jpg"))
{
    m_SceneName = "CubeScene";
    
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
    
 
    m_CubeGPUData->Prepare(const_cast<float*>(TexturedCube), sizeof(TexturedCube));

}

CubeScene::~CubeScene() {
    //Reset Callback
    glfwSetCursorPosCallback(Game::m_Window, [](GLFWwindow* window, double xPos, double yPos)
	{});
    
}
