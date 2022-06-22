#include "Game.h"
#include "Scene/ColoursScene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

GLFWwindow * Game::m_Window = nullptr;

void Game::Loop() {
    try {
     m_Scenes.back()->Update();
     m_Scenes.back()->Render();   
    }
    catch (const std::exception &e) {
			std::cerr << "ERROR IN SCENE: " << m_Scenes.back()->m_SceneName << ": " << e.what() << "\nReverting to previous scene...\n";
			m_Scenes.pop_back();
			return;
    }
    catch (...)
		{
			std::cerr << "ERROR IN SCENE: " << m_Scenes.back()->m_SceneName << ": UNKNOWN ERROR\nReverting to previous scene...\n";
			m_Scenes.pop_back();
			return;
		}
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
        if (m_Scenes.back()->m_End)
            m_Scenes.pop_back();

}

void Game::InitOpenGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	if (m_Window== NULL)
	{
		throw std::runtime_error("FATAL ERROR: Failed to create GLFW window");
	}
	glfwMakeContextCurrent(m_Window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		throw std::runtime_error("FATAL ERROR: Failed to initialize GLAD");
	}
	
    glClearDepth(static_cast<GLdouble>(1.0f));
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glfwSwapInterval(1);

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow * window, int width, int height) {glViewport(0, 0, width, height); });
}


void Game::Run() {
    InitOpenGL();
	m_Scenes.emplace_back(std::make_unique<ColoursScene>());
	while ((m_Scenes.size() > 0) && (!glfwWindowShouldClose(m_Window)))
	{
		this->Loop();
	}
	glfwTerminate();
    
}

Game::Game()
{
}


Game::~Game()
{
}
