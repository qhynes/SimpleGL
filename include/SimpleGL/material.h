#pragma once

#include <SimpleGL/shader.h>
#include <SimpleGL/texture.h>

class Material {
public:
    Shader& shader;
    
    Texture& diffuse;
    Texture& specular;
    float shininess = 32.0f;

    Material(Shader& shader, Texture& diffuse, Texture& specular) : shader(shader), diffuse(diffuse), specular(specular) {}

    void bind() const {
        shader.use();

        diffuse.bind(0);
        shader.setInt("material.diffuse", 0);

        specular.bind(1);
        shader.setInt("material.specular", 1);

        shader.setFloat("material.shininess", shininess);
    }
};
