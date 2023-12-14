#pragma once
#include "Rendering/Renderer/Renderer.h"

class World;

class WorldRendererBase : public Renderer
{
public:
    ~WorldRendererBase() override = default;
    void SetWorldToRender(World* inViewedWorld);
    [[nodiscard]] World* GetWorldToRender() const;
    
private:
    World* worldToRender = nullptr;
};
