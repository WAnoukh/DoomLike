#pragma once
#include "WorldRendererBase.h"
#include "glm/glm.hpp"

using namespace glm;

class World;

class TopDownWorldRenderer : WorldRendererBase
{
public:
    vec2 GetPosition() const;
    vec2 GetFrustumSize() const;
    float GetRotation() const;

    void SetPosition(vec2 inPosition);
    void SetFrustumSize(vec2 inFrustumSize);
    void SetRotation(float inRotation);

    void Render() override;
    
private:
    vec2 position;
    vec2 frustumSize;
    float rotation = 0;
};
