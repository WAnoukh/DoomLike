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
    float playerSpeed = 2.5f;
    float playerTurnSpeed = 6.0f;
    if(PlayerController::player == nullptr)
        return;
    vec2 input = vec2(inputManager->IsKeyPressed(GLFW_KEY_W) - inputManager->IsKeyPressed(GLFW_KEY_S),
                      inputManager->IsKeyPressed(GLFW_KEY_Q) - inputManager->IsKeyPressed(GLFW_KEY_E));
    input *= playerSpeed * deltaTime;

    player->Move(input);
    
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

