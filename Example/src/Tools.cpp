#include "Tools.hpp"

ToolManager* ToolManager::instance_ = nullptr;

void booba::addTool(booba::Tool* tool) {
    ToolManager::GetInstance().AddTool(tool);
}

ToolManager::ToolManager() :
activeTool_(nullptr),
tools_(),
textures_()
{
    
}

void ToolPalette::InitTools(Canvas* canvas, ToolManager* manager, const uint64_t amount) {
    for (uint64_t curTool = (manager->GetToolSize() - amount); curTool < manager->GetToolSize(); curTool++) {
        *this += new ToolButton(canvas, manager->GetTool(curTool));
    }
}

void ToolPalette::SetTool(ToolButton* newTool) {
    if (newTool == curActive_)
        return;

    if (curActive_) {
        curActive_->SetClickedState(0);
        curActive_->SetChanged();
    }

    newTool->SetClickedState(1);
    newTool->SetChanged();

    curActive_ = newTool;   
}
