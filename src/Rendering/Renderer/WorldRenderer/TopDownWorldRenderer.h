#pragma once
#include "WorldRendererBase.h"
#include "Application/Application.h"
#include "glm/glm.hpp"

class WorldFeature;
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
    vec2 WorldDeltaToScreenDelta(vec2 inDelta) const;

    const list<WorldFeature*>& GetWorldFeatures();
    void AddWorldFeature(WorldFeature* worldFeature);

    void DrawLine(vec2 startWorld, vec2 endWorld, DLColor color);
    void DrawLine(vec2 startWorld, float angle, float length, DLColor color);
    void DrawCircle(vec2 centerWorld, int radius, DLColor color);

    void CreateWorldFeatures();
    void CreateGridFeatures();
    void CreatePlayerFeature();
private:
    vec2 position = vec2(0.0f);
    vec2 frustumSize = vec2(2);
    float rotation = 0;

    list<WorldFeature*> worldFeatures;

    void DrawWorldFeatures();
    void DrawPlayer();
    void DrawEdges(bool drawEdges = false);
    void DrawGrid();
    void DrawCoordinateSystem(vec2 position);
};
