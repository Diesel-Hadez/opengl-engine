#ifndef POSITION_GPUDATA_H
#define POSITION_GPUDATA_H
#include "GPUData.h"
class Position : public GPUData {
public:
    virtual void Prepare(float vertices[], std::size_t size) override;
    Position();
    ~Position();
};

#endif

