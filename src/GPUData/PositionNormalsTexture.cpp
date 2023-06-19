#include "GPUData/PositionNormalsTexture.h"

void PositionNormalsTexture::Prepare(float vertices[], std::size_t size) {
    GPUData::Prepare(vertices, size);
}
PositionNormalsTexture::PositionNormalsTexture() {
    // Position coordinates
    AddVec3();

    // Normal Coordinates
    AddVec3();

    // Texture Coordinates
    AddVec2();
}
PositionNormalsTexture::~PositionNormalsTexture() {}
