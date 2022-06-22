#ifndef GPUDATA_H
#define GPUDATA_H
#include <vector>

class GPUData {
protected:
    std::vector<int> m_Variables;
    
    unsigned int VAO, VBO;
    
    void AddVec4() {m_Variables.emplace_back(4);}
    void AddVec3() {m_Variables.emplace_back(3);}
    void AddVec2() {m_Variables.emplace_back(2);}
    void AddVec1() {m_Variables.emplace_back(1);}
public:
    void Bind();
    virtual void Prepare(float data[], std::size_t size) = 0;
    GPUData() = default;
    virtual ~GPUData() = default;
};

#endif
