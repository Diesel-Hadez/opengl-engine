#include "Scene/ImguiScene.h"
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
	
	static ImGuiIO* io;
	static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	static bool show_demo_window = true;
}
void ImguiScene::Update() {
	constexpr double timeStep = 1.0 / 120.0;
	double accumulator {0.0};
	currentFrame   = glfwGetTime();
	m_DeltaTime    = currentFrame - lastFrame;
	lastFrame      = currentFrame;
	accumulator += m_DeltaTime;
	
	if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		this->m_End = true;
	
	while (accumulator >= timeStep) {		
		accumulator -= timeStep;
	}
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	
}

void ImguiScene::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImguiScene::ImguiScene():
m_DeltaTime(0.0f)
{
    m_SceneName = "ImguiScene";
	
}

ImguiScene::~ImguiScene() {
}

