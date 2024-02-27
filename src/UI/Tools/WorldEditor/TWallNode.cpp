#include "TWallNode.h"

#include "Scene/World/WorldGeometry/Edge.h"

void TEdgeNode::AddNeighbor(TEdgeNode* inNeighbor)
{
    neighbors.insert(inNeighbor);
}

void TEdgeNode::RemoveNeighbor(TEdgeNode* inNeighbor)
{
    neighbors.erase(inNeighbor);
}

void TEdgeNode::GetNetwork(std::set<TEdgeNode*>& outNetwork)
{
    if(outNetwork.contains(this))
    {
        return;
    }
    outNetwork.insert(this);
    for(auto neighbor : neighbors)
    {
        neighbor->GetNetwork(outNetwork);
    }
}

const std::set<TEdgeNode*>& TEdgeNode::GetNeighbors() const
{
    return neighbors;
}

void TEdgeNode::AddEdgePoint(Edge* inEdge, unsigned inPointIndex)
{
    edgePoints.push_back({inEdge, inPointIndex});
}

bool TEdgeNode::TryGetPosition(glm::vec2& outPosition) const
{
    if(edgePoints.empty())
    {
        return false;
    }
    outPosition = edgePoints.front().edge->GetPosition(edgePoints.front().pointIndex);
    return true;
}

bool TEdgeNode::IsPositionMatching(glm::vec2 inPosition, float inEpsilon) const
{
    for (auto& edgePoint : edgePoints)
    {
        if(glm::distance(edgePoint.edge->GetPosition(edgePoint.pointIndex), inPosition) > inEpsilon)
        {
            return false;
        }
    }
    return true;
}

void TEdgeNode::SetPosition(const glm::vec2& inPosition)
{
    for (auto& edgePoint : edgePoints)
    {
        edgePoint.edge->SetPosition(edgePoint.pointIndex, inPosition);
    }
}

