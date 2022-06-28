#ifndef PLANESCENE_H
#define PLANESCENE_H

#include <memory>

#include "Scene.h"

class Shader;
class FPCamera;
class Plane;
class PlaneScene: public Scene {
private:
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<FPCamera> m_FPCamera;
    std::unique_ptr<Plane> m_Plane;
    float m_DeltaTime;
public:
    virtual void Update() override;
    virtual void Render() override;
    PlaneScene();
    ~PlaneScene();
};

#endif

