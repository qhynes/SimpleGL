#pragma once

#include <string>

#include <SimpleGL/transform.h>

class Mesh;
class Material;

class Object {
public:
    bool enabled = true;

    static int count;
    int id;

    std::string name;

    Transform transform;

    Mesh* mesh = nullptr;
    Material* material = nullptr;

    Object();
    Object(std::string name);

    void drawGui();
};
