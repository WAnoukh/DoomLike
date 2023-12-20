#pragma once
#include "WMinimapViewport.h"
#include "UI/Tools/WorldEditor/TWorldEditor.h"

class WWorldEditor
{
public:
    //~WWorldEditor() override;
    //void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset) override;
    //void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods) override;
    //void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos) override;
    //void SetMinimapRenderer(MinimapRenderer* inTopDownWorldRenderer) override;
private:
    bool TryToSelectWallNode(vec2 pos, float radius, TWallNode*& outWallNode);
    bool TryToSelectWallNodeFromMouse(ImVec2 mousePos, float radius,TWallNode*& outWallNode);
    
    TWorldEditor worldEditor;
    TWallNode* selectedWallNode = nullptr;
};
