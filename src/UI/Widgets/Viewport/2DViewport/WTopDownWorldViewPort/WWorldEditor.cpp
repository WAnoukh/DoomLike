#include "WWorldEditor.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"
#include "Rendering/Renderer/WorldRenderer/WorldEditorRenderer.h"

void WWorldEditor::ScrollCallBackEvent(bool guiWantToCapture, double xOffset, double yOffset)
{
    WViewport2D::ScrollCallBackEvent(guiWantToCapture, xOffset, yOffset);
}

void WWorldEditor::MouseButtonCallBackEvent(bool guiWantToCapture, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        const auto mousePos = ImGui::GetMousePos();
        if (!TryToSelectWallNodeFromMouse(selectedWallNode))
        {
            worldEditorRenderer->SelectNode(selectedWallNode, false);
            selectedWallNode = nullptr;
        }
        else
        {
            worldEditorRenderer->SelectNode(selectedWallNode, true);
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        worldEditorRenderer->SelectNode(selectedWallNode, false);
        selectedWallNode = nullptr;
    }

    WViewport2D::MouseButtonCallBackEvent(guiWantToCapture, button, action, mods);
}

void WWorldEditor::MousePositionCallBackEvent(bool guiWantToCapture, double xPos, double yPos)
{
    WViewport2D::MousePositionCallBackEvent(guiWantToCapture, xPos, yPos);
}

WorldEditorRenderer* WWorldEditor::GetWorldEditorRenderer() const
{
    return worldEditorRenderer;
}

void WWorldEditor::SetWorldEditorRenderer(WorldEditorRenderer* inWorldEditorRenderer)
{
    worldEditorRenderer = inWorldEditorRenderer;
    if (worldEditorRenderer != nullptr)
    {
        SetViewPortTexture(worldEditorRenderer->GetRenderedTexture().GetTextureId());
        worldEditorRenderer->SetWorldEditor(&worldEditor);
        worldEditor.SetWorld(worldEditorRenderer->GetWorldToRender());
        worldEditor.NodifyWorld();
        worldEditorRenderer->CreateGridFeatures();
        worldEditorRenderer->CreateWorldFeatures();
        worldEditorRenderer->SendEdgeNodesToRenderer();
        worldEditorRenderer->CreatePlayerFeature();
    }
}

void WWorldEditor::Tick(float deltaTime)
{
    WViewport2D::Tick(deltaTime);
    if (selectedWallNode != nullptr)
    {
        const auto mousePos = GetMousePosInTextureSpace();
        const auto mousePosVec2 = vec2(mousePos.x, mousePos.y);
        const auto mousePosViewport = GetWorldEditorRenderer()->ScreenSpaceToWorldSpace(mousePosVec2);
        selectedWallNode->SetPosition(mousePosViewport);
    }
    if (worldEditorRenderer == nullptr)
    {
        std::cerr << "WWorldEditor::Tick : worldEditorRenderer is nullptr" << std::endl;
        return;
    }
    worldEditorRenderer->SetFrustumSize(vec2(GetDisplayedZoom()));
}

void WWorldEditor::ApplyPanning(const float x, const float y)
{
    vec2 position = worldEditorRenderer->GetPosition();
    const auto windowSize = vec2(GetWindowSize().x, GetWindowSize().y);
    const auto panWorld = vec2(x, y) / windowSize;
    const vec2 worldPanning = panWorld * worldEditorRenderer->GetFrustumSize();
    position -= worldPanning * vec2(1, -1);
    return worldEditorRenderer->SetPosition(position);
}

void WWorldEditor::RenderViewPort()
{
    if (worldEditorRenderer == nullptr)
    {
        std::cerr << "WWorldEditor::RenderViewPort : worldEditorRenderer is nullptr" << std::endl;
        return;
    }
    worldEditorRenderer->Render();
}

ImVec2 WWorldEditor::GetMousePosInTextureSpace()
{
    WorldEditorRenderer* worldEditorRenderer = GetWorldEditorRenderer();
    if (worldEditorRenderer == nullptr)
    {
        std::cerr << "WWorldEditor::TryToSelectWallNodeFromMouse : worldEditorRenderer is nullptr" << std::endl;
        return ImVec2();
    }
    const auto mousePos = ImGui::GetMousePos();
    const auto viewportPos = GetViewPortPos();
    const auto viewportSize = GetViewPortSize();
    const auto tewtureSize = worldEditorRenderer->GetRenderedTexture().GetSize();
    return ImVec2((mousePos.x - viewportPos.x) / viewportSize.x * tewtureSize.x,
                                   (1.0f-(mousePos.y - viewportPos.y) / viewportSize.y) * tewtureSize.y);
}

bool WWorldEditor::TryToSelectWallNode(vec2 pos, float radius, TEdgeNode*& outWallNode)
{
    return worldEditor.GetClosestNodeInRadius(pos, radius, outWallNode);
}

bool WWorldEditor::TryToSelectWallNodeFromMouse(TEdgeNode*& outWallNode, float radius)
{
    const auto mousePos = GetMousePosInTextureSpace();
    const auto mousePosVec2 = vec2(mousePos.x, mousePos.y);
    const auto mousePosViewport = worldEditorRenderer->ScreenSpaceToWorldSpace(mousePosVec2);
    const auto radiusViewport = worldEditorRenderer->ScreenDeltaToWorldDelta(vec2(radius, radius));
    return TryToSelectWallNode(mousePosViewport, radiusViewport.x, outWallNode);
}
