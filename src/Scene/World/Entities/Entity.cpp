#include "Entity.h"

#include <corecrt_math_defines.h>
#include <iostream>
#include <math.h>

#include "Scene/World/World.h"
#include "Scene/World/Rays/Ray.h"

vec3 Entity::GetPosition() const
{
    return position;
}

float Entity::GetRotation() const
{
    return rotation;
}

void Entity::SetPosition(vec3 inPosition)
{
    position = inPosition;
}

void Entity::SetRotation(float inRotation)
{
    rotation = inRotation;
}

void Entity::Turn(float angle)
{
    rotation += angle;
}

void Entity::Foward(float distance)
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

void Entity::Move(vec2 relativeSpeed)
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

void Entity::Strafe(float distance)
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

void Entity::Init()
{
}

void Entity::Tick(float deltaTime)
{
}

void Entity::SetWorld(World* inWorld)
{
    world = inWorld;
}
