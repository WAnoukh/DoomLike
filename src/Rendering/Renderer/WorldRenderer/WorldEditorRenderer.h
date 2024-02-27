#pragma once
#include "TopDownWorldRenderer.h"

class WFEdgeNode;
class TEdgeNode;
class TWorldEditor;

class WorldEditorRenderer : public TopDownWorldRenderer
{
public:
    void Render() override;

    void SetWorldToRender(World* inViewedWorld) override;

    void SendEdgeNodesToRenderer();

    void SetWorldEditor(TWorldEditor* inWorldEditor);

    void SelectNode(TEdgeNode* inNode, bool inSelect);

private:
    TWorldEditor* worldEditor = nullptr;
    std::map<TEdgeNode*, WFEdgeNode*> edgeNodesToFeatures;
};
