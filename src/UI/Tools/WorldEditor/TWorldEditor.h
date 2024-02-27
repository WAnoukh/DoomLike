#pragma once
#include "TWallNode.h"
#include "Application/Application.h"
#include "Application/Application.h"

class World;

class TWorldEditor
{
public:
    ~TWorldEditor();
    
    void SetWorld(World* inWorld);
    void NodifyWorld(float mergingDistance = 0.01f);

    bool GetClosestNodeInRadius(const glm::vec2& inPosition, float inRadius, TEdgeNode*& outNode) const;

    const std::list<TEdgeNode*>& GetWallNodes() const;
    
private:
    World* world = nullptr;
    std::list<TEdgeNode*> wallNodes;
};
