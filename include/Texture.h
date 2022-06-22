#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <glad/glad.h>

class Texture{
private:
    unsigned int m_TextureId;;
public:
    
    void Bind(GLenum unit);
    
    Texture(const Texture&) = delete;
    Texture(const std::string& filename);
    ~Texture() = default;
};

#endif
