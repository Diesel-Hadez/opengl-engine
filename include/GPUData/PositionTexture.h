#ifndef POSITIONTEXTURE_H
#define POSITIONTEXTURE_H
#include "GPUData.h"
class PositionTexture : public GPUData {
public:
    virtual void Prepare(float vertices[], std::size_t size) override;
    PositionTexture();
    ~PositionTexture();
};

#endif
