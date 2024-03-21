#include "Player.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <math.h>

#include "Scene/World/World.h"
#include "Scene/World/Rays/Ray.h"

vec3 Player::GetPosition() const
{
    return position;
}

float Player::GetRotation() const
{
    return rotation;
}

void Player::SetPosition(vec3 inPosition)
{
    position = inPosition;
}

void Player::SetRotation(float inRotation)
{
    rotation = inRotation;
}

void Player::Turn(float angle)
{
    rotation += angle;
}

void Player::Foward(float distance)
{
    if(world == nullptr)
    {
        std::cout << "Entity::Move: world is nullptr" << std::endl;
        return;
    }
    const float distanceDirection = distance > 0 ? rotation : rotation + M_PI;
    Ray forwardRay(position, distanceDirection);
    HitResult hitResult;
    float minDist = abs(distance);
    if(world->RayCastOnEdges(forwardRay,hitResult, true))
    {
        float safeDist = max (hitResult.distance -0.01f, 0.0f);
        if(safeDist< minDist)
        {
            minDist = safeDist;
        }
    }
    position.x += minDist * cos(distanceDirection);
    position.y += minDist * sin(distanceDirection);
}

void Player::Move(vec2 relativeSpeed)
{
    if(relativeSpeed.y != 0)
    {
        Strafe(relativeSpeed.y);
    }
    if(relativeSpeed.x != 0)
    {
        Foward(relativeSpeed.x);
    }
}

void Player::Strafe(float distance)
{
    if(world == nullptr)
    {
        std::cout << "Entity::Move: world is nullptr" << std::endl;
        return;
    }
    const float distanceDirection = distance > 0 ? rotation + M_PI / 2 : rotation - M_PI / 2;
    Ray sideRay(position, distanceDirection);
    HitResult hitResult;
    float minDist = abs(distance);
    if(world->RayCastOnEdges(sideRay,hitResult, true))
    {
        float safeDist = max (hitResult.distance -0.01f, 0.0f);
        if(safeDist< minDist)
        {
            minDist = safeDist;
        }
    }
    position.x += minDist * cos(distanceDirection);
    position.y += minDist * sin(distanceDirection);
}

void Player::Init()
{
}

void Player::Tick(float deltaTime)
{
}

void Player::SetWorld(World* inWorld)
{
    world = inWorld;
}
