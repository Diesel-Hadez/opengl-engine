#ifndef CUBESCENE_H
#define CUBESCENE_H

#include <memory>

#include "Scene.h"

class PositionTexture;
class Shader;
class FPCamera;
class CubeScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<PositionTexture> m_CubeGPUData;
    float m_DeltaTime;
    
    unsigned int texture1;
public:
    virtual void Update() override;
    virtual void Render() override;
    CubeScene();
    ~CubeScene();
};

#endif
