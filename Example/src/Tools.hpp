#pragma once

#include <filesystem>
#include "../../tools.hpp"

#include "Image.hpp"

class Canvas;

class ToolButton;

class ToolManager {
    private:
        static ToolManager* instance_;
        booba::Tool* activeTool_;

        std::vector<booba::Tool*> tools_;
        std::vector<sf::Texture*> textures_; 

        ToolManager();
    public:
        ToolManager(const ToolManager& manager)            = delete;
        ToolManager& operator=(const ToolManager& manager) = delete;

        static ToolManager& GetInstance() {
            if (!instance_) {
                instance_ = new ToolManager();
            }

            return *instance_;
        }

        void ApplyActive(booba::Image* image, const booba::Event* event) {
            if (activeTool_) {
                activeTool_->apply(image, event);
            }
        }

        void SelectTool(booba::Tool* newTool) {
            activeTool_ = newTool;
        }

        void AddTool(booba::Tool* newTool) {
            tools_.push_back(newTool);

            sf::Texture* newTexture = new sf::Texture();

            newTexture->loadFromFile(newTool->getTexture());

            textures_.push_back(newTexture);
        }

        uint64_t GetToolSize() {
            return tools_.size();
        }

        booba::Tool* GetTool(const uint64_t toolIdx) {
            return tools_[toolIdx];
        }

        sf::Texture* GetToolTexture(const uint32_t toolIdx) {
            return textures_[toolIdx];
        }
};

// Widget that controls toolsButtons
class ToolPalette : public DynamicWindow {
    private:
        ToolButton* curActive_;

    public:
        ToolPalette(uint32_t x, uint32_t y) :
        DynamicWindow(x, y),
        curActive_(nullptr)
        {}

        ToolPalette(const ToolPalette& palette)            = delete;
        ToolPalette& operator=(const ToolPalette& palette) = delete;

        void InitTools(Canvas* canvas, ToolManager* manager, const uint64_t amount);
        void SetTool(ToolButton* newTool);
};

class Canvas : public ImageWindow {
    private:
        uint32_t curToolIdx_;
    public:
        ToolManager& toolManager_;
        ToolPalette* toolPalette_;

        Canvas(uint32_t x, uint32_t y, uint32_t width, uint32_t height, ToolPalette* palette) :
        ImageWindow(x, y, width, height),
        curToolIdx_(0),
        toolManager_(ToolManager::GetInstance()),
        toolPalette_(palette)
        {
            std::string dlPath = "./Plugins";
            
            for (const auto& curFile : std::filesystem::directory_iterator(dlPath)) {
                if (curFile.is_directory()) {
                    continue;
                }

                void* dlHandler = dlopen(curFile.path().c_str(), RTLD_LAZY);
                
                if (dlHandler) {
                    void (*initFunc)()     = nullptr;
                    *((void**)(&initFunc)) = dlsym(dlHandler, "init_module");

                    (*initFunc)();
                }
                else {
                    fprintf(stderr, "Unable to open plugin: %s\n", dlerror());
                }
            }
            
            toolPalette_->InitTools(this, &toolManager_, toolManager_.GetToolSize());
        }

        Canvas(const Canvas& canvas)            = delete;
        Canvas& operator=(const Canvas& canvas) = delete;

        booba::Event ConvertToStandartEvent(const Event& event) {
            Event standartEvent = event;

            if (event.type_ == EventType::MousePressed) {
                CordsPair convertedCords = ConvertRealXY({event.Oleg_.mbedata.x, event.Oleg_.mbedata.y});

                standartEvent.Oleg_.mbedata.x = convertedCords.x;
                standartEvent.Oleg_.mbedata.y = convertedCords.y;
            }
            else if (event.type_ == EventType::MouseMoved) {
                CordsPair convertedCords = ConvertRealXY({event.Oleg_.motion.x, event.Oleg_.motion.y});

                standartEvent.Oleg_.motion.rel_x = convertedCords.x;
                standartEvent.Oleg_.motion.rel_y = convertedCords.y;
            }

            return *reinterpret_cast<booba::Event*>(&standartEvent);
        }

        virtual void OnClick(const Event& curEvent) override {
            Window::OnClick(curEvent);

            if (IsClicked({curEvent.Oleg_.mbedata.x, curEvent.Oleg_.mbedata.y})) {
                booba::Event stEvent = ConvertToStandartEvent(curEvent);

                toolManager_.ApplyActive(&image_, &stEvent);
            }
        }

        virtual void OnMove(const Event& curEvent) override {
            Window::OnMove(curEvent);

            if (IsClicked({curEvent.Oleg_.mbedata.x, curEvent.Oleg_.mbedata.y})) {
                booba::Event stEvent = ConvertToStandartEvent(curEvent);
                
                toolManager_.ApplyActive(&image_, &stEvent);
            }
        }

        virtual void OnRelease(const Event& curEvent) override {
            Window::OnRelease(curEvent);

            booba::Event stEvent = ConvertToStandartEvent(curEvent);
            toolManager_.ApplyActive(&image_, &stEvent);
        }

        ~Canvas() {}
};

const uint32_t DefaultToolButtonWidth  = 50;
const uint32_t DefaultToolButtonHeight = 50;

class ToolButton : public Button {
    private:
        Canvas*       canvas_;

        booba::Tool*  tool_;
        sf::Texture*  toolTexture_;

    public:
        ToolButton(Canvas* curCanvas, booba::Tool* curTool) :
        Button(0, 0, DefaultToolButtonWidth, DefaultToolButtonHeight),
        canvas_(curCanvas), tool_(curTool), toolTexture_(nullptr)
        {
            clickAction_ = new MethodCaller<ToolButton, CordsPair>(this, &ToolButton::SetMeToCanvas);
        
            for (uint32_t toolIdx = 0; toolIdx < canvas_->toolManager_.GetToolSize(); toolIdx++) {
                if (canvas_->toolManager_.GetTool(toolIdx) == curTool) {
                    toolTexture_ = canvas_->toolManager_.GetToolTexture(toolIdx);
                }
            }
        }

        ToolButton(const ToolButton& toolB)            = default;
        ToolButton& operator=(const ToolButton& toolB) = default;

        virtual void FlagClicked([[maybe_unused]] const CordsPair& cords) override {}
        virtual void FlagReleased() override {}

        void SetMeToCanvas(const CordsPair& cords) {
            if (!IsClicked(cords)) {
                return;
            }

            canvas_->toolManager_.SelectTool(tool_);
            ((ToolPalette*)parent_)->SetTool(this);
        }

        virtual void ReDraw() override {
            Button::ReDraw();

            sf::Texture texture;

            Rectangle iconRect({DefaultToolButtonWidth, DefaultToolButtonHeight, 0, 0});
            iconRect.Draw(widgetContainer_, toolTexture_);
        }
}; 

