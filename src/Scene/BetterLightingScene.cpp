#include "Scene/BetterLightingScene.h"
#include "Game.h"
#include "Camera/FPCamera.h"
#include "Shader.h"
#include "GPUData/Position.h"
#include "GPUData/PositionNormals.h"
#include "SampleVertices.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace {
    float currentFrame = 0;
    float lastFrame    = 0;
}  // namespace
void BetterLightingScene::Update() {
    currentFrame = glfwGetTime();
    m_DeltaTime  = currentFrame - lastFrame;
    lastFrame    = currentFrame;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_W) == GLFW_PRESS)
        m_FPCamera->ProcessKeyboard(Camera::Movement::FORWARD, m_DeltaTime);
    if (glfwGetKey(Game::m_Window, GLFW_KEY_S) == GLFW_PRESS)
        m_FPCamera->ProcessKeyboard(Camera::Movement::BACKWARD, m_DeltaTime);
    if (glfwGetKey(Game::m_Window, GLFW_KEY_A) == GLFW_PRESS)
        m_FPCamera->ProcessKeyboard(Camera::Movement::LEFT, m_DeltaTime);
    if (glfwGetKey(Game::m_Window, GLFW_KEY_D) == GLFW_PRESS)
        m_FPCamera->ProcessKeyboard(Camera::Movement::RIGHT, m_DeltaTime);
    if (glfwGetKey(Game::m_Window, GLFW_KEY_Q) == GLFW_PRESS)
        m_FPCamera->ProcessKeyboard(Camera::Movement::UP, m_DeltaTime);
    if (glfwGetKey(Game::m_Window, GLFW_KEY_E) == GLFW_PRESS)
        m_FPCamera->ProcessKeyboard(Camera::Movement::DOWN, m_DeltaTime);

    float     speed = 5.0f * m_DeltaTime;
    glm::vec3 front = glm::vec3(1.0 * speed, 0.0, 0.0);
    glm::vec3 top   = glm::vec3(0.0, 1.0 * speed, 0.0);
    glm::vec3 left  = glm::vec3(0.0, 0.0, 1.0 * speed);

    if (glfwGetKey(Game::m_Window, GLFW_KEY_I) == GLFW_PRESS)
        lampPos += front;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_K) == GLFW_PRESS)
        lampPos -= front;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_J) == GLFW_PRESS)
        lampPos += left;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_L) == GLFW_PRESS)
        lampPos -= left;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_U) == GLFW_PRESS)
        lampPos += top;
    if (glfwGetKey(Game::m_Window, GLFW_KEY_O) == GLFW_PRESS)
        lampPos -= top;

    if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Game::GetInstance().PopScene();
}

void BetterLightingScene::Render() {
    m_Shader->Use();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->Use();

    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model      = glm::mat4(1.0f);

    projection = glm::perspective(glm::radians(45.0f),
                                  (float)(WINDOW_WIDTH) / (float)(WINDOW_HEIGHT),
                                  0.1f,
                                  100.0f);
    view       = m_FPCamera->GetViewMatrix();

    m_Shader->Set<glm::mat4>("projection", projection);
    m_Shader->Set<glm::mat4>("view", view);
    m_Shader->Set<glm::mat4>("model", model);

    m_Shader->Set<glm::vec3>("viewPos", m_FPCamera->Position);

    m_Shader->Set<glm::vec3>("material.ambient", glm::vec3(1.f, 0.5f, 0.31f));
    m_Shader->Set<glm::vec3>("material.diffuse", glm::vec3(1.f, 0.5f, 0.31f));
    m_Shader->Set<glm::vec3>("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_Shader->Set<float>("material.shininess", 32.f);

    m_Shader->Set<glm::vec3>("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_Shader->Set<glm::vec3>("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_Shader->Set<glm::vec3>("light.specular", glm::vec3(1.f, 1.f, 1.f));
    m_Shader->Set<glm::vec3>("light.position", lampPos);

    m_CubeGPUData->Bind();

    glDrawArrays(GL_TRIANGLES, 0, NormalCubeVertices);

    m_LightCubeShader->Use();
    model = glm::translate(glm::mat4(1.0f), lampPos);
    model = glm::scale(model, glm::vec3(0.3f));
    m_LightCubeShader->Set<glm::mat4>("model", model);
    m_LightCubeShader->Set<glm::mat4>("projection", projection);
    m_LightCubeShader->Set<glm::mat4>("view", view);
    m_LightGPUData->Bind();
    glDrawArrays(GL_TRIANGLES, 0, CubeVertices);
}

BetterLightingScene::BetterLightingScene()
    : m_Shader(
        std::make_unique<Shader>("../resources/lightingDiffuse.vs", "../resources/materials.fs"))
    , m_LightCubeShader(std::make_unique<Shader>("../resources/lightingcube1.vs",
                                                 "../resources/lightingcube1.fs"))
    , m_FPCamera(std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f)))
    , m_DeltaTime(0.0f)
    , m_CubeGPUData(std::make_unique<PositionNormals>())
    , m_LightGPUData(std::make_unique<Position>())
    , lampPos(glm::vec3(0.f, 1.f, 0.5f)) {
    m_SceneName = "DiffuseScene";
    m_CubeGPUData->Prepare(const_cast<float*>(NormalCube), sizeof(NormalCube));
    m_LightGPUData->Prepare(const_cast<float*>(Cube), sizeof(Cube));
}

BetterLightingScene::~BetterLightingScene() {}
