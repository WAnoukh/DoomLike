#pragma once

class TopDownWorldRenderer;

class WorldFeature
{
public:
    virtual ~WorldFeature() = default;
    virtual void Draw(TopDownWorldRenderer* renderer) = 0;
    
};



