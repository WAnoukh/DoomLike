#include "WViewport2D.h"

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "imgui.h"
#include "Helpers/UsefullFunc.h"


void WViewport2D::SetZoom(float inZoom)
{
    targetZoom = inZoom;
}

float WViewport2D::GetDisplayedZoom() const 
{
    return displayedZoom;
}

void WViewport2D::StartPanning(const float x, const float y)
{
    lastMousePos = {x,y};
    isPanning = true;
}

void WViewport2D::ApplyPanning(const float x, const float y)
{
    const auto screenZoom = ImVec2(GetDisplayedZoom(),-GetDisplayedZoom());
    const auto windowSize = GetWindowSize();
    targetPanOffset = {
                        (targetPanOffset.x + (x / windowSize.x) * screenZoom.x),
                        (targetPanOffset.y + (y / windowSize.y) * screenZoom.y) 
                        }; 
}

void WViewport2D::StopPanning(bool savePan)
{
    isPanning = false;
}

bool WViewport2D::IsPanning() const
{
    return isPanning;
}

vec2 WViewport2D::GetDisplayedOffset() const
{
    return vec2(displayedOffset.x, displayedOffset.y);
}

void WViewport2D::Tick(float deltaTime)
{
    displayedZoom = AnoukhFun::Damp(displayedZoom, targetZoom, lerpSpeed, deltaTime);
    //const auto vPanOffset = vec2(displayedOffset.x, displayedOffset.y);
    //const auto vTargetPanOffset = vec2(targetPanOffset.x, targetPanOffset.y);
    //const auto newOffset = AnoukhFun::Damp<vec2>( vPanOffset , vTargetPanOffset, lerpSpeed, deltaTime);
    //displayedOffset = ImVec2(newOffset.x, newOffset.y);
}

void WViewport2D::RenderUI()
{
    WViewportBase::RenderUI();
}

void WViewport2D::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset)
{
    if (IsWindowHovered())
    {
        lerpSpeed = 0.0f;
        SetZoom(GetDisplayedZoom() * (1.0f - static_cast<float>(yOffset)*0.1f));
        ImGui::SetWindowFocus(GetGuiName());
    }
}

void WViewport2D::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods)
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

void WViewport2D::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
    if(IsPanning())
    {
        ImVec2 mousePos = {static_cast<float>(xPos),static_cast<float>(yPos)};
        ApplyPanning(mousePos.x - lastMousePos.x, mousePos.y - lastMousePos.y);
        lastMousePos = mousePos;
        ImGui::SetWindowFocus(GetGuiName());
    }
}