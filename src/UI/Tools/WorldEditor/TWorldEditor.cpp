#include "TWorldEditor.h"

#include <iostream>

#include "Scene/World/World.h"

TWorldEditor::~TWorldEditor()
{
    for (TEdgeNode*& wallNode : wallNodes)
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
    std::map<Edge*, TEdgeNode*> edgeToNode;
    for(Edge* edge : edges)
    {
        bool firstEdgeMatched = false;
        bool secondEdgeMatched = false;
        for(auto& wallNode : wallNodes)
        {
            if(!firstEdgeMatched && wallNode->IsPositionMatching(edge->GetStart(), mergingDistance))
            {
                wallNode->AddEdgePoint(edge, 0);
                if(edgeToNode.count(edge))
                {
                    TEdgeNode* otherNode = edgeToNode.at(edge);
                    if(otherNode != wallNode)
                    {
                        wallNode->AddNeighbor(otherNode);
                        otherNode->AddNeighbor(wallNode);
                    }
                }
                else
                {
                    edgeToNode[edge] = wallNode;
                }
                firstEdgeMatched = true;
            }
            if(!secondEdgeMatched && wallNode->IsPositionMatching(edge->GetEnd(), mergingDistance))
            {
                wallNode->AddEdgePoint(edge, 1);
                if(edgeToNode.count(edge))
                {
                    TEdgeNode* otherNode = edgeToNode.at(edge);
                    if(otherNode != wallNode)
                    {
                        wallNode->AddNeighbor(otherNode);
                        otherNode->AddNeighbor(wallNode);
                    }
                }
                else
                {
                    edgeToNode[edge] = wallNode;
                }
                secondEdgeMatched = true;
            }
            if(firstEdgeMatched && secondEdgeMatched)
            {
                break;
            }
        }
        if (!firstEdgeMatched)
        {
            TEdgeNode* newWallNode = new TEdgeNode();
            newWallNode->AddEdgePoint(edge, 0);
            wallNodes.push_back(newWallNode);
            edgeToNode[edge] = newWallNode;
        }
        if (!secondEdgeMatched)
        {
            TEdgeNode* newWallNode = new TEdgeNode();
            newWallNode->AddEdgePoint(edge, 1);
            wallNodes.push_back(newWallNode);
            edgeToNode[edge] = newWallNode;
        }
    }
}

bool TWorldEditor::GetClosestNodeInRadius(const glm::vec2& inPosition, float inRadius, TEdgeNode*& outNode) const
{
    float distance = 0;
    bool firstNode = true;
    for(auto& wallNode : wallNodes)
    {
        glm::vec2 wallNodePosition;
        if(wallNode->TryGetPosition(wallNodePosition))
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

const std::list<TEdgeNode*>& TWorldEditor::GetWallNodes() const
{
    return wallNodes;
}
