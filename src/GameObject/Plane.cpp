#include "GameObject/Plane.h"
#include "Shader.h"
#include "GPUData/PositionNormals.h"
#include "SampleVertices.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Plane::Plane(const glm::vec3& position, double width, double length): 
    m_CubeGPUData(std::make_unique<PositionNormals>()) {
    m_Position = position;
    m_Width = width;
    m_Length = length;
    m_Height = 1.f;
    
    m_CubeGPUData->Prepare(const_cast<float*>(NormalCube), sizeof(NormalCube));
}

// Assumes shader sets projection and view appropriately
void Plane::Render(Shader* shader=nullptr){
    if (shader) {
            shader->Use();
            glm::mat4 model(1.f);
            model = glm::translate(model, m_Position);
            model = glm::scale(model, glm::vec3(m_Width, m_Height, m_Length));
            shader->Set<glm::mat4>("model", model);
            shader->Set<glm::vec3>("lightPos", m_Position + glm::vec3(0.0f, 1.0f, 0.0f));
            shader->Set<glm::vec3>("objectColor", glm::vec3(0.5f, 0.0f, 0.0f));
            shader->Set<glm::vec3>("lightColor", glm::vec3(1.0f));
            
            m_CubeGPUData->Bind();
            glDrawArrays(GL_TRIANGLES, 0, NormalCubeVertices);
    }
}
