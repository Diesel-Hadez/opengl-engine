#ifndef COLOURSSCENE_H
#define COLOURSSCENE_H

#include <memory>

#include "Scene.h"

class Position;
class Shader;
class FPCamera;
class Texture;
class ColoursScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Shader> m_LightCubeShader;
    std::unique_ptr<FPCamera> m_FPCamera;
    
    std::unique_ptr<Position> m_CubeGPUData;
    std::unique_ptr<Position> m_LightGPUData;
    float m_DeltaTime;
    
public:
    virtual void Update() override;
    virtual void Render() override;
    ColoursScene();
    ~ColoursScene();
};

#endif

