#include "WorldEditorRenderer.h"

#include <iostream>

#include "Scene/World/WorldGeometry/Edge.h"
#include "TopDownWorldFeatures/WorldFeatures/WFEdgeNode.h"
#include "UI/Tools/WorldEditor/TWorldEditor.h"

void WorldEditorRenderer::Render()
{
    Texture& texture = GetRenderedTexture();
    texture.Fill(DLColor::BLACK);
    TopDownWorldRenderer::Render();
}

void WorldEditorRenderer::SetWorldToRender(World* inViewedWorld)
{
    TopDownWorldRenderer::SetWorldToRender(inViewedWorld);
}

void WorldEditorRenderer::SendEdgeNodesToRenderer()
{
    if(worldEditor == nullptr)
    {
        std::cerr << "WorldEditor::SendEdgeNodesToRenderer : worldEditor is nullptr" << std::endl;
        return;
    }
    std::list<TEdgeNode*> nodes = worldEditor->GetWallNodes();
    std::map<TEdgeNode*, WFEdgeNode*> reviewedNodes;
    for(TEdgeNode* node : nodes)
    {
        if(node == nullptr)
        {
            std::cerr << "WorldEditor::SendEdgeNodesToRenderer : node is nullptr" << std::endl;
            continue;
        }
        WFEdgeNode* edgeNode = new WFEdgeNode();
        edgeNode->SetEdgeNode(node);
        reviewedNodes[node] = edgeNode;
        for(TEdgeNode* neighbor : node->GetNeighbors())
        {
            if(reviewedNodes.count(neighbor))
            {
                reviewedNodes.at(neighbor)->AddNeighbor(edgeNode);
            }
        }
        edgeNodesToFeatures[node] = edgeNode;
        AddWorldFeature(edgeNode);
    }
    
}

void WorldEditorRenderer::SetWorldEditor(TWorldEditor* inWorldEditor)
{
    worldEditor = inWorldEditor;
}

void WorldEditorRenderer::SelectNode(TEdgeNode* inNode, bool inSelect)
{
    if(edgeNodesToFeatures.count(inNode))
    {
        edgeNodesToFeatures.at(inNode)->SetNodeColor(inSelect ? DLColor::RED : DLColor::BLUE);
    }
}
