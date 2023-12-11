#pragma once
#include "glm/glm.hpp"
using namespace glm;
class Entity
{
public:
    vec3 GetPosition() const;
    float GetRotation() const;
    void SetPosition(vec3 inPosition);
    void SetRotation(float inRotation);
private:
    vec3 position;
    float rotation = 0.0f;
};
