#ifndef BETTER_LIGHTING_SCENE_H
#define BETTER_LIGHTING_SCENE_H

#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"

class PositionNormals;
class Position;
class Shader;
class FPCamera;
class BetterLightingScene : public Scene {
private:
    std::unique_ptr<Shader>   m_Shader;
    std::unique_ptr<Shader>   m_LightCubeShader;
    std::unique_ptr<FPCamera> m_FPCamera;

    std::unique_ptr<PositionNormals> m_CubeGPUData;
    std::unique_ptr<Position>        m_LightGPUData;
    float                            m_DeltaTime;
    glm::vec3                        lampPos;

public:
    virtual void Update() override;
    virtual void Render() override;
    BetterLightingScene();
    ~BetterLightingScene();
};

#endif
