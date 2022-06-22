#include "GPUData/PositionTexture.h"
#include <glad/glad.h>
#include <numeric>

#include <iostream>

void PositionTexture::Prepare(float vertices[], std::size_t size) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

   
    int total_size = std::accumulate(m_Variables.begin(), m_Variables.end(), 0);
    int sum = 0;
    int i = 0;
    for (auto cur_size : m_Variables) {
        glVertexAttribPointer(i, cur_size, GL_FLOAT, GL_FALSE, total_size * sizeof(float), (void*)(sum * sizeof(float)));
        glEnableVertexAttribArray(i);
        sum += cur_size;
        i++;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
PositionTexture::PositionTexture(){
    // Position coordinates
    AddVec3();
    
    // Texture Coordinates
    AddVec2();
}
PositionTexture::~PositionTexture(){}
