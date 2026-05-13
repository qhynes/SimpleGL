#pragma once

// get OpenGL headers
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// get necessary libraries
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // program ID used to refer to program
    unsigned int ID;

    // constructor that creates shader
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // function to use shader
    void use() const;
    
    // utility functions to set uniform values
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};
