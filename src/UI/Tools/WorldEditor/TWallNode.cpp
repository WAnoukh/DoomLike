#include "TWallNode.h"

#include "Scene/World/WorldGeometry/Edge.h"

void TWallNode::AddNeighbor(TWallNode* inNeighbor)
{
    neighbors.insert(inNeighbor);
}

void TWallNode::RemoveNeighbor(TWallNode* inNeighbor)
{
    neighbors.erase(inNeighbor);
}

void TWallNode::GetNetwork(std::set<TWallNode*>& outNetwork)
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

void TWallNode::AddEdgePoint(Edge* inEdge, unsigned inPointIndex)
{
    edgePoints.push_back({inEdge, inPointIndex});
}

bool TWallNode::GetPosition(glm::vec2& outPosition) const
{
    if(edgePoints.empty())
    {
        return false;
    }
    outPosition = edgePoints.front().edge->GetPosition(edgePoints.front().pointIndex);
    return true;
}

bool TWallNode::IsPositionMatching(glm::vec2 inPosition, float inEpsilon) const
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

void TWallNode::SetPosition(const glm::vec2& inPosition)
{
    for (auto& edgePoint : edgePoints)
    {
        edgePoint.edge->SetPosition(edgePoint.pointIndex, inPosition);
    }
}

