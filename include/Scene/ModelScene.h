#ifndef MODEL_SCENE_H
#define MODEL_SCENE_H

#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"
#include "Model/Model.h"

class FPCamera;
class Shader;
class Position;
class ModelScene : public Scene {
private:
    std::unique_ptr<Shader>   m_Shader;
    std::unique_ptr<Shader>   m_HighlightShader;
    std::unique_ptr<Shader>   m_LightCubeShader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<Position> m_LightGPUData;
    Model::Model              m_Model;
    float                     m_DeltaTime;
    glm::vec3                 lampPos;
    bool                      m_Highlight;

public:
    virtual void Update() override;
    virtual void Render() override;
    ModelScene();
    ~ModelScene();
};

#endif
