#include "PlayerController.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Entity.h"
#include "Application/Application.h"

void PlayerController::Init()
{
    inputManager = &Application::GetInstance().GetInputManager();
}

void PlayerController::Tick(float deltaTime)
{
    float playerSpeed = 0.4f;
    float playerTurnSpeed = 6.0f;
    if(PlayerController::player == nullptr)
        return;

    if (inputManager->IsKeyPressed(GLFW_KEY_W))
    {
        player->Foward(playerSpeed * deltaTime);
    }
    if (inputManager->IsKeyPressed(GLFW_KEY_S))
    {
        player->Foward(-playerSpeed * deltaTime);
    }
    if (inputManager->IsKeyPressed(GLFW_KEY_Q))
    {
        player->Strafe(playerSpeed * deltaTime);
    }
    if (inputManager->IsKeyPressed(GLFW_KEY_E))
    {
        player->Strafe(-playerSpeed * deltaTime);
    }
    if (inputManager->IsKeyPressed(GLFW_KEY_A))
    {
        player->Turn(playerTurnSpeed * deltaTime);
    }
    if (inputManager->IsKeyPressed(GLFW_KEY_D))
    {
        player->Turn(-playerTurnSpeed * deltaTime);
    }
}

void PlayerController::SetPlayer(Entity* inPlayer)
{
    player = inPlayer;
}

