#include <SimpleGL/light.h>

#include <SimpleGL/shader.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <iostream>

glm::vec3 directionFromYawPitch(float yaw, float pitch) {
    glm::vec3 dir;

    dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    dir.y = sin(glm::radians(pitch));
    dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    return glm::normalize(dir);
}

int Light::count = 0;

Light::Light(LightType type) : type(type) {
    id = count;
    name = "Light " + std::to_string(id);
    count++;
}

Light::Light(LightType type, std::string name) : type(type), name(name) {
    id = count;
    count++;
}

void DirectionalLight::uploadToShader(Shader& shader, int index) {
    std::string base = "dirLight";
    shader.setVec3(base + ".radiance", color * intensity);
    direction = directionFromYawPitch(yaw, pitch);
    shader.setVec3(base + ".direction", glm::normalize(direction));
}

void PointLight::uploadToShader(Shader& shader, int index) {
    std::string base = "pointLight[" + std::to_string(index) + "]";
    shader.setVec3(base + ".radiance", color * intensity);
    shader.setVec3(base + ".position", position);
    shader.setFloat(base + ".constant", constant);
    shader.setFloat(base + ".linear", linear);
    shader.setFloat(base + ".quadratic", quadratic);
}

void SpotLight::uploadToShader(Shader& shader, int index) {
    std::string base = "spotLight[" + std::to_string(index) + "]";
    shader.setVec3(base + ".radiance", color * intensity);
    shader.setVec3(base + ".position", position);
    shader.setVec3(base + ".direction", glm::normalize(direction));
    shader.setFloat(base + "innerCuttoff", innerCutoff);
    shader.setFloat(base + "outerCuttoff", outerCutoff);
    shader.setFloat(base + ".constant", constant);
    shader.setFloat(base + ".linear", linear);
    shader.setFloat(base + ".quadratic", quadratic);
}

void DirectionalLight::drawGui() {
    ImGui::Checkbox("Enabled", &enabled);
    ImGui::ColorEdit3("Color", &color.x);
    ImGui::DragFloat("Intensity", &intensity, 0.05f);

    ImGui::DragFloat("Yaw", &yaw, 0.5f, -180.0f, 180.0f);
    ImGui::DragFloat("Pitch", &pitch, 0.5f, -89.0f, 89.0f);
}

void PointLight::drawGui() {
    ImGui::Checkbox("Enabled", &enabled);
    ImGui::ColorEdit3("Color", &color.x);
    ImGui::DragFloat("Intensity", &intensity, 0.05f);
    ImGui::DragFloat3("Position", &position.x, 0.1f);
    ImGui::DragFloat("Constant", &constant, 0.01f);
    ImGui::DragFloat("Linear", &linear, 0.01f);
    ImGui::DragFloat("Quadratic", &quadratic, 0.01f);
}

void SpotLight::drawGui() {
    ImGui::Checkbox("Enabled", &enabled);
    ImGui::ColorEdit3("Color", &color.x);
    ImGui::DragFloat("Intensity", &intensity, 0.05f);
    ImGui::DragFloat3("Position", &position.x, 0.1f);
    ImGui::DragFloat3("Direction", &direction.x, 0.1f);
    ImGui::DragFloat("Inner Cutoff", &innerCutoff, 0.05f);
    ImGui::DragFloat("Outer Cutoff", &outerCutoff, 0.05f);
    ImGui::DragFloat("Intensity", &intensity, 0.05f);
    ImGui::DragFloat("Constant", &constant, 0.01f);
    ImGui::DragFloat("Linear", &linear, 0.01f);
    ImGui::DragFloat("Quadratic", &quadratic, 0.01f);
}
