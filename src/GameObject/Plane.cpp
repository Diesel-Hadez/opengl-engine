#include "GameObject/Plane.h"
#include "Shader.h"
#include "GPUData/Position.h"
#include "SampleVertices.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Plane::Plane(const glm::vec3& position, double width, double length): 
    m_CubeGPUData(std::make_unique<Position>()) {
    m_Position = position;
    m_Width = width;
    m_Length = length;
    m_Height = 1.f;
    
    m_CubeGPUData->Prepare(const_cast<float*>(Cube), sizeof(Cube));
}

// Assumes shader sets projection and view appropriately
void Plane::Render(Shader* shader=nullptr){
    if (shader) {
            shader->Use();
            glm::mat4 model(1.f);
            model = glm::scale(model, glm::vec3(m_Width, m_Height, m_Length));
            model = glm::translate(model, m_Position);
            shader->Set<glm::mat4>("model", model);
            shader->Set<glm::vec3>("color", glm::vec3(0.5f, 0.0f, 0.0f));
            
            m_CubeGPUData->Bind();
            glDrawArrays(GL_TRIANGLES, 0, CubeVertices);
    }
}