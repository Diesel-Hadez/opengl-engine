#ifndef LIGHT_MAP_SCENE_H
#define LIGHT_MAP_SCENE_H

#include <memory>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.h"

class PositionNormalsTexture;
class Position;
class Shader;
class FPCamera;
class Texture;
class LightMapScene : public Scene {
private:
    std::unique_ptr<Shader>   m_Shader;
    std::unique_ptr<Shader>   m_LightCubeShader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<Texture>  m_CubeTexture;

    std::unique_ptr<PositionNormalsTexture> m_CubeGPUData;
    std::unique_ptr<Position>               m_LightGPUData;
    float                                   m_DeltaTime;
    glm::vec3                               lampPos;

public:
    virtual void Update() override;
    virtual void Render() override;
    LightMapScene();
    ~LightMapScene();
};

#endif
