#include "GPUData.h"
#include <glad/glad.h>


void GPUData::Bind() {
    glBindVertexArray(this->VAO);
}
