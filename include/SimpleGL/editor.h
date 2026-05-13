#pragma once

class Scene;

class EditorGui {
public:
    void draw(Scene& scene);

private:
    int selectedObjectIndex = -1;
    int selectedLightIndex = -1;

    void drawSceneHierarchy(Scene& scene);
    void drawInspector(Scene& scene);
    void drawRendererSettings(Scene& scene);
};
