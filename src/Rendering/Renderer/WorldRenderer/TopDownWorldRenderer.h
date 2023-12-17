#pragma once
#include "WorldRendererBase.h"
#include "glm/glm.hpp"
#include "Scene/World/WorldExemples/BasicRoom/BasicRoom_WorldExemple.h"
#include "Scene/World/WorldExemples/BasicRoom/BasicRoom_WorldExemple.h"
#include "Scene/World/WorldExemples/BasicRoom/BasicRoom_WorldExemple.h"
#include "Scene/World/WorldExemples/BasicRoom/BasicRoom_WorldExemple.h"

using namespace glm;

class World;

class TopDownWorldRenderer : public WorldRendererBase
{
public:
    ~TopDownWorldRenderer() override = default;

    void Init() override;
    
    vec2 GetPosition() const;
    vec2 GetFrustumSize() const;
    float GetRotation() const;

    void SetPosition(vec2 inPosition);
    void SetFrustumSize(vec2 inFrustumSize);
    void SetRotation(float inRotation);

    void Render() override;
    
    vec2 WorldSpaceToScreenSpace(vec2 inPosition) const;
    vec2 ScreenSpaceToWorldSpace(vec2 inPosition) const;
    vec2 ScreenDeltaToWorldDelta(vec2 inDelta) const;

private:
    vec2 position = vec2(0.0f);
    vec2 frustumSize = vec2(2);
    float rotation = 0;

    void DrawPlayer();
    void DrawEdges(bool drawEdges = false);
    void DrawGrid();
    void DrawCoordinateSystem(vec2 position);
};
