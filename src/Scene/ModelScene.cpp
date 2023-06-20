#include "Scene/ModelScene.h"
#include "Game.h"
#include "Camera/FPCamera.h"
#include "Shader.h"
#include "GPUData/Position.h"
#include "SampleVertices.h"

#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace {
    float currentFrame = 0;
    float lastFrame    = 0;

    bool       highlightPressed = false;
    const auto HIGHLIGHT_KEY    = GLFW_KEY_X;
}  // namespace
void ModelScene::Update() {
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

    if (!highlightPressed && glfwGetKey(Game::m_Window, HIGHLIGHT_KEY) == GLFW_PRESS) {
        highlightPressed = true;
    }
    if (highlightPressed && glfwGetKey(Game::m_Window, HIGHLIGHT_KEY) == GLFW_RELEASE) {
        highlightPressed = false;
        m_Highlight      = !m_Highlight;
    }

    if (glfwGetKey(Game::m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        Game::GetInstance().PopScene();
}

void ModelScene::Render() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glStencilMask(0x00);

    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);

    m_Shader->Use();
    // m_CubeTexture->Bind(GL_TEXTURE0);
    // m_CubeSpecularTexture->Bind(GL_TEXTURE1);

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

    m_Shader->Set<glm::vec3>("material.diffuse", glm::vec3(1.f, 0.5f, 0.31f));
    // m_Shader->Set<glm::vec3>("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    m_Shader->Set<float>("material.shininess", 32.f);
    m_Shader->Set<int>("material.specular", 1);
    m_Shader->Set<int>("material.diffuse", 0);

    m_Shader->Set<glm::vec3>("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_Shader->Set<glm::vec3>("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    m_Shader->Set<glm::vec3>("light.specular", glm::vec3(1.f, 1.f, 1.f));
    m_Shader->Set<glm::vec3>("light.position", lampPos);
    m_Model.Draw(*m_Shader);

    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    m_HighlightShader->Use();
    model = glm::scale(model, glm::vec3(1.01));
    m_HighlightShader->Set<glm::mat4>("model", model);
    m_HighlightShader->Set<glm::mat4>("projection", projection);
    m_HighlightShader->Set<glm::mat4>("view", view);
    if (m_Highlight) {
        m_Model.Draw(*m_HighlightShader);
    }

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH_TEST);

    // m_CubeGPUData->Bind();
    //
    // glDrawArrays(GL_TRIANGLES, 0, NormalTexturedCubeVertices);

    m_LightCubeShader->Use();
    model = glm::translate(glm::mat4(1.0f), lampPos);
    model = glm::scale(model, glm::vec3(0.3f));
    m_LightCubeShader->Set<glm::mat4>("model", model);
    m_LightCubeShader->Set<glm::mat4>("projection", projection);
    m_LightCubeShader->Set<glm::mat4>("view", view);
    m_LightGPUData->Bind();
    glDrawArrays(GL_TRIANGLES, 0, CubeVertices);
}

ModelScene::ModelScene()
    : m_Shader(std::make_unique<Shader>("../resources/normaltexturedcube.vs",
                                        "../resources/model_loading.fs"))
    , m_LightCubeShader(std::make_unique<Shader>("../resources/lightingcube1.vs",
                                                 "../resources/lightingcube1.fs"))
    , m_HighlightShader(std::make_unique<Shader>("../resources/lightingcube1.vs",
                                                 "../resources/lightingcube1.fs"))
    , m_Model("../resources/models/backpack/backpack.obj")
    , m_FPCamera(std::make_unique<FPCamera>(glm::vec3(0.0f, 0.0f, 3.0f)))
    , m_DeltaTime(0.0f)
    , m_LightGPUData(std::make_unique<Position>())
    , lampPos(glm::vec3(0.f, 1.f, 0.5f))
    , m_Highlight(false) {
    m_SceneName = "ModelScene";
    m_LightGPUData->Prepare(const_cast<float*>(Cube), sizeof(Cube));
}

ModelScene::~ModelScene() {}
