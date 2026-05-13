#include <SimpleGL/object.h>

#include <SimpleGL/mesh.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <numbers>

int Object::count = 1;

Object::Object() {
    id = count;
    name = "Object " + std::to_string(id);
    count++;
}

Object::Object(std::string name) : name(name) {
    id = count;
    count++;
}

void Object::drawGui() {
    ImGui::Checkbox("Enabled", &enabled);
    ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
    ImGui::SliderFloat3("Rotation", &transform.rotation.x, 0.0f, 360.0f);
    ImGui::DragFloat("Uniform Scale", &transform.uniformScale, 0.05f, 0.01f, 100.0f);
    ImGui::DragFloat3("Scale XYZ", &transform.scale.x, 0.01f);
}
