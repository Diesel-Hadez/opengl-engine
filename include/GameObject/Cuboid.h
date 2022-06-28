#ifndef CUBOID_H
#define CUBOID_H
#include "GameObject.h"
#include <memory>

class PositionNormals;
class Shader;
class Cuboid: public GameObject {
private:
    std::unique_ptr<PositionNormals> m_CubeGPUData;
    
    double m_Width;
    double m_Length;
    double m_Height;
public:
    Cuboid(const glm::vec3& position, double width, double height, double length);
    
    virtual void Render(Shader* shader) override;
    virtual void Update(double) override;
};

#endif
