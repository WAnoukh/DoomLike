#pragma once
#include "Rendering/Renderer/WorldRenderer/TopDownWorldFeatures/WorldFeature.h"
#include "Rendering/Color/DLColor.h"

class TopDownWorldRenderer;
class Player;

class WFPlayer : public WorldFeature
{
public:
    WFPlayer(Player* playerEntity) : player(playerEntity) {}

    void Draw(TopDownWorldRenderer* renderer);

    void SetPlayer(Player* inPlayer);

    void SetPositionColor(DLColor inPositionColor);
    void SetDirectionColor(DLColor inDirectionColor);
private:
    Player* player = nullptr;
    DLColor positionColor = DLColor::RED;
    DLColor directionColor = DLColor::YELLOW;
};
