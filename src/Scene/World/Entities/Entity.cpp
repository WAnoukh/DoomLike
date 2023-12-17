#include "Entity.h"

#include <corecrt_math_defines.h>
#include <math.h>

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
    position.x += distance * cos(rotation);
    position.y += distance * sin(rotation);
}

void Entity::Strafe(float distance)
{
    position.x += distance * cos(rotation + M_PI / 2);
    position.y += distance * sin(rotation + M_PI / 2);
}

void Entity::Init()
{
}

void Entity::Tick(float deltaTime)
{
}
