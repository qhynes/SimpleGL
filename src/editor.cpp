#include <SimpleGL/editor.h>

#include <SimpleGL/scene.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

void EditorGui::draw(Scene& scene) {
    drawSceneHierarchy(scene);
    drawInspector(scene);
    drawRendererSettings(scene);
}

void EditorGui::drawSceneHierarchy(Scene& scene) {
    ImGui::Begin("Scene");
    

    if (ImGui::TreeNode("Objects")) {
        for (int i = 0; i < scene.objects.size(); i++) {
            bool selected = selectedObjectIndex == i;

            if (ImGui::Selectable(scene.objects[i]->name.c_str(), selected)) {
                selectedObjectIndex = i;
                selectedLightIndex = -1;
            }
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Lights")) {
        for (int i = 0; i < scene.lights.size(); i++) {
            bool selected = selectedLightIndex == i;

            if (ImGui::Selectable(scene.lights[i]->name.c_str(), selected)) {
                selectedLightIndex = i;
                selectedObjectIndex = -1;
            }
        }

        ImGui::TreePop();
    }

    ImGui::End();
}

void EditorGui::drawInspector(Scene& scene) {
    ImGui::Begin("Inspector");

    if (selectedObjectIndex >= 0 && selectedObjectIndex < scene.objects.size()) {
        Object& object = *scene.objects[selectedObjectIndex];

        char nameBuffer[64];
        std::strncpy(nameBuffer, object.name.c_str(), sizeof(nameBuffer));
        nameBuffer[sizeof(nameBuffer) - 1] = '\0';

        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            object.name = nameBuffer;
        }

        object.drawGui();

        // ImGui::DragFloat3("Position", &object.transform.position.x, 0.1f);
        // ImGui::DragFloat3("Rotation", &object.transform.rotation.x, 1.0f);
        // ImGui::DragFloat3("Scale", &object.transform.scale.x, 0.1f);
    }

    if (selectedLightIndex >= 0 && selectedLightIndex < scene.lights.size()) {
        scene.lights[selectedLightIndex]->drawGui();
    }

    ImGui::End();
}

void EditorGui::drawRendererSettings(Scene& scene) {
    ImGui::Begin("Renderer Settings");

    ImGui::ColorEdit3("Background", &scene.backgroundColor.x);
    ImGui::ColorEdit3("Ambient Color", &scene.ambientColor.x);
    ImGui::DragFloat("Ambient Strength", &scene.ambientStrength, 0.01f, 0.0f, 1.0f);

    ImGui::End();
}
