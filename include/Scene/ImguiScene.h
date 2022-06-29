#ifndef IMGUISCENE_H
#define IMGUISCENE_H

#include <memory>
#include "Scene.h"

class ImguiScene: public Scene {
private:
    float m_DeltaTime;
 
    
    const float timeStep = 1.0f / 60.0f;
public:
    virtual void Update() override;
    virtual void Render() override;
    ImguiScene();
    ~ImguiScene();
};

#endif

