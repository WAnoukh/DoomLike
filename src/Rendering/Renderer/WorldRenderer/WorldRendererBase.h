#pragma once
#include "Rendering/Renderer/Renderer.h"

class World;

class WorldRendererBase : Renderer
{
public:
    void SetWorldToRender(World* inViewedWorld);
    World* GetWorldToRender() const;
    
private:
    World* worldToRender = nullptr;
};
