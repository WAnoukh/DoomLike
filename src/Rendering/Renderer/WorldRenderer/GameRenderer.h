#pragma once
#include "WorldRendererBase.h"

class GameRenderer : public WorldRendererBase
{
public:
    ~GameRenderer() override = default;
    void Render() override;
    void Init() override;
};
