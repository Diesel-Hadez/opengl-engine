#include "Game.h"
#include "Scene/MenuScene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GLFW/glfw3.h>


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include <reactphysics3d/reactphysics3d.h>

GLFWwindow * Game::m_Window = nullptr;
Game::PhysicsCommonPtr Game::m_PhysicsCommon = std::make_unique<PhysicsCommon>();

namespace {
	static ImGuiIO* io;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);	
}

void Game::Loop() {
    try {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_Scenes.back()->Update();
		m_Scenes.back()->Render();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

void Game::InitImgui()
{	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	io = &ImGui::GetIO();
	
	ImGui::StyleColorsDark();
	
	ImGui_ImplGlfw_InitForOpenGL(Game::m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}



void Game::Run() {
    InitOpenGL();
	InitImgui();
	m_Scenes.emplace_back(std::make_unique<MenuScene>());
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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
