#include "WWorldEditor.h"

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"
/*
void WWorldEditor::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset)
{
    WMinimapViewport::ScrollCallBackEvent(window, guiWantToCapture, xOffset, yOffset);
}

void WWorldEditor::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods)
{
    WMinimapViewport::MouseButtonCallBackEvent(window, guiWantToCapture, button, action, mods);
}

void WWorldEditor::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
    WMinimapViewport::MousePositionCallBackEvent(window, guiWantToCapture, xPos, yPos);
}

void WWorldEditor::SetMinimapRenderer(MinimapRenderer* inTopDownWorldRenderer)
{
    WMinimapViewport::SetMinimapRenderer(inTopDownWorldRenderer);
    if(inTopDownWorldRenderer != nullptr)
    {
        worldEditor.SetWorld(inTopDownWorldRenderer->GetWorldToRender());
        worldEditor.NodifyWorld();
    }
}

bool WWorldEditor::TryToSelectWallNode(vec2 pos, float radius,TWallNode*& outWallNode)
{
    return worldEditor.GetClosestNodeInRadius(pos, radius, outWallNode);
}

bool WWorldEditor::TryToSelectWallNodeFromMouse(ImVec2 mousePos, float radius, TWallNode*& outWallNode)
{
    ImVec2 viewPortPos = ScreenSpaceToViewportSpace(mousePos);
    return true;
}*/
