#pragma once
#include "Rendering/Renderer/WorldRenderer/TopDownWorldFeatures/WorldFeature.h"
#include "Rendering/Color/DLColor.h"

class TopDownWorldRenderer;
class Entity;

class WFPlayer : public WorldFeature
{
public:
    WFPlayer(Entity* playerEntity) : player(playerEntity) {}

    void Draw(TopDownWorldRenderer* renderer);

    void SetPlayer(Entity* inPlayer);

    void SetPositionColor(DLColor inPositionColor);
    void SetDirectionColor(DLColor inDirectionColor);
private:
    Entity* player = nullptr;
    DLColor positionColor = DLColor::RED;
    DLColor directionColor = DLColor::YELLOW;
};
