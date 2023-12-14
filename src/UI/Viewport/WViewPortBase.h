#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui.h>

#include "UI/UIWidget.h"

class Renderer;

class WViewPortBase : public UIWidget
{
public:
    WViewPortBase(const char* name = "ViewportBase") : guiName(name)
    {
    }

    ~WViewPortBase() override;

    void Init() override;
    void RenderUI() override;
    void PreRenderViewPort();
    virtual void RenderViewPort();
    
    virtual bool ScreenToTexture(const float x, const float y, float& outX, float& outY) = 0;

    bool IsWindowHovered();
    
    const char* GetGuiName();

    ImVec2 GetViewPortPos();

    ImVec2 GetViewPortSize();
private:
    const char* guiName;
    ImVec2 lastSize = ImVec2(0,0);
    ImVec2 viewPortPos = ImVec2(0,0);
    unsigned int viewPortTexture = 0;
    unsigned int FBO = 0;
    
    bool isWindowHovered = false;
};
