#ifndef CUBESCENE_H
#define CUBESCENE_H

#include <memory>

#include "Scene.h"

class PositionTexture;
class Shader;
class FPCamera;
class Texture;
class CubeScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<PositionTexture> m_CubeGPUData;
    std::unique_ptr<Texture> m_CubeTexture;
    float m_DeltaTime;
public:
    virtual void Update() override;
    virtual void Render() override;
    CubeScene();
    ~CubeScene();
};

#endif
