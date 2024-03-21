#pragma once
#include "DLObject.h"
#include "glm/glm.hpp"
class World;
using namespace glm;

class Player : public DLObject
{
public:
    vec3 GetPosition() const;
    float GetRotation() const;
    
    void SetPosition(vec3 inPosition);
    void SetRotation(float inRotation);

    void Turn(float angle);
    void Foward(float distance);
    void Move(vec2 relativeSpeed);
    void Strafe(float distance);

    void Init() override;
    void Tick(float deltaTime) override;
    void SetWorld(World* inWorld);
private:
    vec3 position;
    float rotation = 0.0f;
    World* world = nullptr;
};
