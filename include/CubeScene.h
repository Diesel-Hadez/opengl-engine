#ifndef CUBESCENE_H
#define CUBESCENE_H

#include <memory>

#include "Scene.h"

class Shader;
class FPCamera;
class CubeScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<FPCamera> m_FPCamera;
    float m_DeltaTime;
    
    unsigned int texture1;
    unsigned int VAO, VBO;
public:
    virtual void Update() override;
    virtual void Render() override;
    CubeScene();
    ~CubeScene();
};

#endif
