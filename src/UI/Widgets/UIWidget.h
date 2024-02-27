#pragma once
#include "DLObject.h"

class UIWidget : public DLObject
{
public:
    virtual ~UIWidget() = default;
    
    virtual void RenderUI() = 0;

    virtual void ScrollCallBackEvent(bool guiWantToCapture, double xOffset, double yOffset) = 0;
    virtual void MouseButtonCallBackEvent(bool guiWantToCapture, int button, int action, int mods) = 0;
    virtual void MousePositionCallBackEvent(bool guiWantToCapture, double xPos, double yPos) = 0;
};
