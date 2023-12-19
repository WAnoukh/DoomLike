#include "TWorldEditor.h"

#include <iostream>

#include "Scene/World/World.h"

TWorldEditor::~TWorldEditor()
{
    for (TWallNode*& wallNode : wallNodes)
    {
        delete wallNode;
    }
}

void TWorldEditor::SetWorld(World* inWorld)
{
    world = inWorld;
}

void TWorldEditor::NodifyWorld(float mergingDistance)
{
    if(!world)
    {
        std::cout << "TWorldEditor::NodifyWorld: No world to nodify" << std::endl;
        return;
    }
    auto edges = world->GetEdges();
    for(Edge* edge : edges)
    {
        bool firstEdgeMatched = false;
        bool secondEdgeMatched = false;
        for(auto& wallNode : wallNodes)
        {
            if(!firstEdgeMatched && wallNode->IsPositionMatching(edge->GetStart(), mergingDistance))
            {
                wallNode->AddEdgePoint(edge, 0);
                firstEdgeMatched = true;
            }
            if(!secondEdgeMatched && wallNode->IsPositionMatching(edge->GetEnd(), mergingDistance))
            {
                wallNode->AddEdgePoint(edge, 1);
                secondEdgeMatched = true;
            }
            if(firstEdgeMatched && secondEdgeMatched)
            {
                break;
            }
        }
        if (!firstEdgeMatched)
        {
            TWallNode* newWallNode = new TWallNode();
            newWallNode->AddEdgePoint(edge, 0);
            wallNodes.push_back(newWallNode);
        }
        if (!secondEdgeMatched)
        {
            TWallNode* newWallNode = new TWallNode();
            newWallNode->AddEdgePoint(edge, 1);
            wallNodes.push_back(newWallNode);
        }
    }
}

bool TWorldEditor::GetClosestNodeInRadius(const glm::vec2& inPosition, float inRadius, TWallNode*& outNode) const
{
    float distance = 0;
    bool firstNode = true;
    for(auto& wallNode : wallNodes)
    {
        glm::vec2 wallNodePosition;
        if(wallNode->GetPosition(wallNodePosition))
        {
            float currentDistance = glm::distance(wallNodePosition, inPosition);
            if(currentDistance < inRadius)
            {
                if(firstNode)
                {
                    distance = currentDistance;
                    firstNode = false;
                    outNode = wallNode;
                }
                else if(currentDistance < distance)
                {
                    distance = currentDistance;
                    outNode = wallNode;
                }
            }
        }
    }
    return !firstNode;
}
