#include "Scene/MenuScene.h"
#include "Shader.h"
#include "Game.h"
#include "Camera/FPCamera.h"
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
#include "Scene/BetterLightingScene.h"

namespace {
    float currentFrame = 0;
    float lastFrame    = 0;
}  // namespace
void MenuScene::Update() {
    glfwSetInputMode(Game::m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
    ImGui::Begin("Scene");

    if (ImGui::Button("ColoursScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<ColoursScene>());
        this->OnPause();
    }
    if (ImGui::Button("CubeScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<CubeScene>());
        this->OnPause();
    }
    if (ImGui::Button("DiffuseScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<DiffuseScene>());
        this->OnPause();
    }
    if (ImGui::Button("BetterLightingScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<BetterLightingScene>());
        this->OnPause();
    }
    if (ImGui::Button("ImGuiScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<ImguiScene>());
        this->OnPause();
    }
    if (ImGui::Button("PhysicsScene")) {
        Game::GetInstance().PushScene(std::make_unique<PhysicsScene>());
    }
    if (ImGui::Button("PlaneScene")) {
        Game::GetInstance().m_Scenes.emplace_back(std::make_unique<PlaneScene>());
        this->OnPause();
    }

    if (ImGui::Button("Exit")) {
        Game::GetInstance().PopScene();
    }
    ImGui::End();
}

void MenuScene::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

MenuScene::MenuScene()
    : m_DeltaTime(0.0f) {
    m_SceneName = "MenuScene";
}

MenuScene::~MenuScene() {}
