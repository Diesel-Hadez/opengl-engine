#ifndef PLANE_H
#define PLANE_H
#include "GameObject.h"
#include <memory>

class Position;
class Shader;
class Plane: public GameObject {
private:
    std::unique_ptr<Position> m_CubeGPUData;
    
    double m_Width;
    double m_Length;
    double m_Height;
public:
    Plane(const glm::vec3& position, double width, double length);
    
    void Render(Shader* shader);
};

#endif
