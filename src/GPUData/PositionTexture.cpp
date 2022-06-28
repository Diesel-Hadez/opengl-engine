#include "GPUData/PositionTexture.h"

void PositionTexture::Prepare(float vertices[], std::size_t size) {
    GPUData::Prepare(vertices, size);
}
PositionTexture::PositionTexture(){
    // Position coordinates
    AddVec3();
    
    // Texture Coordinates
    AddVec2();
}
PositionTexture::~PositionTexture(){}
