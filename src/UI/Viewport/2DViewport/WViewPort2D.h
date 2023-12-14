#pragma once

#include "UI/Viewport/WViewPortBase.h"

class WViewPort2D : public WViewPortBase
{
public:
    WViewPort2D(const char* name = "ViewPort2D") : WViewPortBase(name){}

    //Zoom
    void SetZoom(float inZoom);
    float GetDisplayedZoom() const;
    
    //Panning
    void StartPanning(const float x, const float y);
    void ApplyPanning(const float x, const float y);
    void StopPanning(bool savePan = true);
    bool IsPanning() const;
    ImVec2 GetDisplayedOffset() const;    

    void Tick(float deltaTime) override;
    void RenderUI() override;

    void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset) override;

    void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) override;

    void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) override;

private:
    inline static const float DEFAULT_VIEWPORT_2D_LERPSPEED = 0.0001f;
    float lerpSpeed = DEFAULT_VIEWPORT_2D_LERPSPEED;
    
    // Panning
    bool isPanning = false;
    ImVec2 lastMousePos = ImVec2(0.0f,0.0f);
    ImVec2 displayedOffset = ImVec2(0.0f,0.0f);
    ImVec2 targetPanOffset = ImVec2(0.0f,0.0f);

    // Zoom
    float displayedZoom = 1.0f;
    float targetZoom = 1.0f;
};
