#include "Entity.h"

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
