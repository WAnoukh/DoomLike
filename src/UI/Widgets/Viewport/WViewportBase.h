#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui.h>

#include "UI/Widgets/UIWidget.h"

class Renderer;

class WViewportBase : public UIWidget
{
public:
    WViewportBase(const char* name = "ViewportBase") : guiName(name)
    {
    }

    ~WViewportBase() override;

    //Getters
    const char* GetGuiName();
    ImVec2 GetViewPortPos();
    ImVec2 GetViewPortSize();
    ImVec2 GetWindowSize() const;
    ImVec2 GetMousePosInViewport();

    //Setters
    void SetViewPortTexture(unsigned int inViewPortTexture);
    
    void Init() override;
    void RenderUI() override;
    void PreRenderViewPort();
    virtual void RenderViewPort();
    
    ImVec2 ScreenSpaceToViewportSpace(ImVec2 screenSpacePos);

    bool IsWindowHovered();
private:
    const char* guiName;
    ImVec2 lastSize = ImVec2(0,0);
    ImVec2 viewPortPos = ImVec2(0,0);
    unsigned int viewPortTexture = 0;
    unsigned int FBO = 0;
    
    bool isWindowHovered = false;
    ImVec2 windowSize = ImVec2(1.0f,1.0f);
};
