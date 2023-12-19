#pragma once

#include <glm/detail/func_packing_simd.inl>
#include <glm/detail/type_vec.hpp>

#include "UI/Widgets/Viewport/WViewPortBase.h"

using namespace glm;

class WViewPort2D : public WViewPortBase
{
public:
    WViewPort2D(const char* name = "ViewPort2D") : WViewPortBase(name){}

    //Zoom
    void SetZoom(float inZoom);
    float GetDisplayedZoom() const;

    //Panning
    void StartPanning(const float x, const float y);
    virtual void ApplyPanning(const float x, const float y) = 0;
    void StopPanning(bool savePan = true);
    bool IsPanning() const;
    vec2 GetDisplayedOffset() const;    

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
