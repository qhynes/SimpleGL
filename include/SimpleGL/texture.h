#pragma once

#include <string>

#include "glad/glad.h"

class Texture {
public:
    Texture(const std::string& texturePath, bool useSRGB);
    Texture(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    static void unbind();

private:
    GLuint m_id = 0;
    int width = 0;
    int height = 0;
    int channels = 0;
};
