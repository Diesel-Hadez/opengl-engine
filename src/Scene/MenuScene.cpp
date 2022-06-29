#include "Scene/MenuScene.h"
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

#include "Scene/ColoursScene.h"
#include "Scene/CubeScene.h"
#include "Scene/DiffuseScene.h"
#include "Scene/ImguiScene.h"
#include "Scene/PhysicsScene.h"
#include "Scene/PlaneScene.h"

namespace {
    float currentFrame = 0;
    float lastFrame    = 0;
}  // namespace
void MenuScene::Update() {
    constexpr double timeStep = 1.0 / 120.0;
    double           accumulator{0.0};
    currentFrame = glfwGetTime();
    m_DeltaTime  = currentFrame - lastFrame;
    lastFrame    = currentFrame;
    accumulator += m_DeltaTime;

    while (accumulator >= timeStep) {
        // Enter update stuff here.

        accumulator -= timeStep;
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Scene");

    if (ImGui::Button("ColoursScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<ColoursScene>());
    }
    if (ImGui::Button("CubeScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<CubeScene>());
    }
    if (ImGui::Button("DiffuseScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<DiffuseScene>());
    }
    if (ImGui::Button("ImGuiScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<ImguiScene>());
    }
    if (ImGui::Button("PhysicsScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<PhysicsScene>());
    }
    if (ImGui::Button("PlaneScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<PlaneScene>());
    }

    if (ImGui::Button("Exit")) {
        this->m_End = true;
    }
    ImGui::End();
}

void MenuScene::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

MenuScene::MenuScene()
    : m_DeltaTime(0.0f) {
    m_SceneName = "MenuScene";
    glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

MenuScene::~MenuScene() {}
