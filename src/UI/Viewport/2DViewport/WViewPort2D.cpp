#include "WViewPort2D.h"

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "Helpers/UsefullFunc.h"


void WViewPort2D::SetZoom(float inZoom)
{
    targetZoom = inZoom;
}

float WViewPort2D::GetDisplayedZoom() const 
{
    return displayedZoom;
}

void WViewPort2D::StartPanning(const float x, const float y)
{
    lastMousePos = {x,y};
    isPanning = true;
}

void WViewPort2D::ApplyPanning(const float x, const float y)
{
    const auto screenZoom = ImVec2(GetDisplayedZoom(),-GetDisplayedZoom());
    const auto windowSize = GetWindowSize();
    targetPanOffset = {
                        (targetPanOffset.x + (x / windowSize.x) * screenZoom.x),
                        (targetPanOffset.y + (y / windowSize.y) * screenZoom.y) 
                        }; 
}

void WViewPort2D::StopPanning(bool savePan)
{
    isPanning = false;
}

bool WViewPort2D::IsPanning() const
{
    return isPanning;
}

vec2 WViewPort2D::GetDisplayedOffset() const
{
    return vec2(displayedOffset.x, displayedOffset.y);
}

void WViewPort2D::Tick(float deltaTime)
{
    displayedZoom = AnoukhFun::Damp(displayedZoom, targetZoom, lerpSpeed, deltaTime);
    //const auto vPanOffset = vec2(displayedOffset.x, displayedOffset.y);
    //const auto vTargetPanOffset = vec2(targetPanOffset.x, targetPanOffset.y);
    //const auto newOffset = AnoukhFun::Damp<vec2>( vPanOffset , vTargetPanOffset, lerpSpeed, deltaTime);
    //displayedOffset = ImVec2(newOffset.x, newOffset.y);
}

void WViewPort2D::RenderUI()
{
    WViewPortBase::RenderUI();
}

void WViewPort2D::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset)
{
    if (IsWindowHovered())
    {
        lerpSpeed = 0.0f;
        SetZoom(GetDisplayedZoom() * (1.0f + static_cast<float>(yOffset)*0.1f));
        ImGui::SetWindowFocus(GetGuiName());
    }
}

void WViewPort2D::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
        {
            if (IsWindowHovered() && !IsPanning())
            {
                lerpSpeed = 0.0f;
                ImVec2 mousePos = ImGui::GetMousePos();
                StartPanning(mousePos.x, mousePos.y);
                ImGui::SetWindowFocus(GetGuiName());
            }
        }
        else if(action == GLFW_RELEASE)
        {
            if(IsPanning())
            {
                StopPanning();
            }
        }
        return;
    }
}

void WViewPort2D::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
    if(IsPanning())
    {
        ImVec2 mousePos = {static_cast<float>(xPos),static_cast<float>(yPos)};
        ApplyPanning(mousePos.x - lastMousePos.x, mousePos.y - lastMousePos.y);
        lastMousePos = mousePos;
        ImGui::SetWindowFocus(GetGuiName());
    }
}