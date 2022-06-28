#ifndef POSITIONNORMALS_H
#define POSITIONNORMALS_H
#include "GPUData.h"
class PositionNormals: public GPUData {
public:
    virtual void Prepare(float vertices[], std::size_t size) override;
    PositionNormals();
    ~PositionNormals();
};

#endif
