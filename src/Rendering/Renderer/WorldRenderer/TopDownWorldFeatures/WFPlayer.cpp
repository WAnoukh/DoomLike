#include "WFPlayer.h"

#include <iostream>

#include "Rendering/Renderer/WorldRenderer/TopDownWorldRenderer.h"
#include "Scene/World/Entities/Player.h"

void WFPlayer::Draw(TopDownWorldRenderer* renderer)
{
    if(renderer == nullptr)
    {
        std::cerr << "WFPlayer::Draw : renderer is null" << std::endl;
        return;
    }
    if(player == nullptr)
    {
        std::cerr << "WFPlayer::Draw : player is null" << std::endl;
        return;
    }
    renderer->DrawLine(player->GetPosition(), player->GetRotation(), 10, directionColor);
    renderer->DrawCircle(player->GetPosition(), 5, positionColor);
}

void WFPlayer::SetPlayer(Player* inPlayer)
{
    player = inPlayer;
}

void WFPlayer::SetPositionColor(DLColor inPositionColor)
{
    positionColor = inPositionColor;
}

void WFPlayer::SetDirectionColor(DLColor inDirectionColor)
{
    directionColor = inDirectionColor;
}
