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

    bool GetClosestNodeInRadius(const glm::vec2& inPosition, float inRadius, TWallNode*& outNode) const;
    
private:
    World* world = nullptr;
    std::list<TWallNode*> wallNodes;
};
