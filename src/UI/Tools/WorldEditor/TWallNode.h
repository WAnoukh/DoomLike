#pragma once
#include <set>
#include <list>
#include <glm/detail/type_vec.hpp>

#include "Scene/World/WorldGeometry/Edge.h"

class Edge;

class TWallNode
{
public:
    
    void AddNeighbor(TWallNode* inNeighbor);
    void RemoveNeighbor(TWallNode* inNeighbor);
    void GetNetwork(std::set<TWallNode*>& outNetwork);
    void AddEdgePoint(Edge* inEdge, unsigned int inPointIndex);
    
    void SetPosition(const glm::vec2& inPosition);
    bool GetPosition(glm::vec2& outPosition) const;
    bool IsPositionMatching(glm::vec2 inPosition, float inEpsilon) const;

private:
    struct EdgePoint
    {
        Edge* edge = nullptr;
        unsigned int pointIndex = 0;
    };
    std::set<TWallNode*> neighbors;
    std::list<EdgePoint> edgePoints;
};
