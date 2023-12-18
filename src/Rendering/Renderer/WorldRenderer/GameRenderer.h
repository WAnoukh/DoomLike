#pragma once
#include "WorldRendererBase.h"

class GameRenderer : public WorldRendererBase
{
public:
    ~GameRenderer() override = default;
    void Render() override;
    void Init() override;

private:
    void RenderWorld();

    float fov = 3.1415926f / 2.0f;
};
