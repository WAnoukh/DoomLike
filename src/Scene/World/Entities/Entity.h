#pragma once
#include "DLObject.h"
#include "glm/glm.hpp"
using namespace glm;

class Entity : public DLObject
{
public:
    vec3 GetPosition() const;
    float GetRotation() const;
    
    void SetPosition(vec3 inPosition);
    void SetRotation(float inRotation);

    void Turn(float angle);
    void Foward(float distance);
    void Strafe(float distance);

    void Init() override;
    void Tick(float deltaTime) override;
private:
    vec3 position;
    float rotation = 0.0f;
};
