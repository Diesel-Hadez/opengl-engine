#include "GPUData/Position.h"
#include <glad/glad.h>

void Position::Prepare(float vertices[], std::size_t size) {
    GPUData::Prepare(vertices, size);
}
Position::Position(){
    // Position coordinates
    AddVec3();
}
Position::~Position(){}

