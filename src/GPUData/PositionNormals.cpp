#include "GPUData/PositionNormals.h"

void PositionNormals::Prepare(float vertices[], std::size_t size) {
    GPUData::Prepare(vertices, size);
}
PositionNormals::PositionNormals(){
    // Position coordinates
    AddVec3();
    
    // Normal Coordinates
    AddVec3();
}
PositionNormals::~PositionNormals(){}
