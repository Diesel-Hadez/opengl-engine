#ifndef POSITIONNORMALSTEXTURE_H
#define POSITIONNORMALSTEXTURE_H
#include "GPUData.h"
class PositionNormalsTexture : public GPUData {
public:
    virtual void Prepare(float vertices[], std::size_t size) override;
    PositionNormalsTexture();
    ~PositionNormalsTexture();
};

#endif
