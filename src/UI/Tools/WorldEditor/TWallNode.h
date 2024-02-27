#pragma once
#include <set>
#include <list>
#include <glm/detail/type_vec.hpp>

#include "Scene/World/WorldGeometry/Edge.h"

class Edge;

class TEdgeNode
{
public:
    void GetNetwork(std::set<TEdgeNode*>& outNetwork);
    const std::set<TEdgeNode*>& GetNeighbors() const;
    
    void AddNeighbor(TEdgeNode* inNeighbor);
    void RemoveNeighbor(TEdgeNode* inNeighbor);
    void AddEdgePoint(Edge* inEdge, unsigned int inPointIndex);
    
    void SetPosition(const glm::vec2& inPosition);
    bool TryGetPosition(glm::vec2& outPosition) const;
    bool IsPositionMatching(glm::vec2 inPosition, float inEpsilon) const;

private:
    struct EdgePoint
    {
        Edge* edge = nullptr;
        unsigned int pointIndex = 0;
    };
    std::set<TEdgeNode*> neighbors;
    std::list<EdgePoint> edgePoints;
};
