#pragma once
#include "DLObject.h"

class InputManager;
class Entity;

class PlayerController : public DLObject
{
public:
    void Init() override;
    void Tick(float deltaTime) override;

    void SetPlayer(Entity* inPlayer);

private:
    Entity* player = nullptr;
    InputManager* inputManager = nullptr;
};
