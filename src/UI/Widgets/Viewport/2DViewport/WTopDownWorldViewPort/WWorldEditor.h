#pragma once
#include "WMinimapViewport.h"
#include "UI/Tools/WorldEditor/TWorldEditor.h"

class WWorldEditor : public WViewport2D
{
public:
    WWorldEditor(const char* name = "WWorldEditor") : WViewport2D(name){}
    ~WWorldEditor() override = default;
    void ScrollCallBackEvent(bool guiWantToCapture, double xOffset, double yOffset) override;
    void MouseButtonCallBackEvent(bool guiWantToCapture, int button, int action, int mods) override;
    void MousePositionCallBackEvent(bool guiWantToCapture, double xPos, double yPos) override;

    WorldEditorRenderer* GetWorldEditorRenderer() const;
    
    void SetWorldEditorRenderer(WorldEditorRenderer* inWorldEditorRenderer);
    
    void Tick(float deltaTime) override;
    void ApplyPanning(const float x, const float y) override;
    void RenderViewPort() override;

    ImVec2 GetMousePosInTextureSpace();
private:
    WorldEditorRenderer* worldEditorRenderer = nullptr;
    TWorldEditor worldEditor;
    TEdgeNode* selectedWallNode = nullptr;

    bool TryToSelectWallNode(vec2 pos, float radius, TEdgeNode*& outWallNode);

    bool TryToSelectWallNodeFromMouse(TEdgeNode*& outWallNode, float radius = 10.0f);
};
