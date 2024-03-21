#pragma once
#include "DLObject.h"

class InputManager;
class Player;

class PlayerController : public DLObject
{
public:
    void Init() override;
    void Tick(float deltaTime) override;

    void SetPlayer(Player* inPlayer);

private:
    Player* player = nullptr;
    InputManager* inputManager = nullptr;
};
