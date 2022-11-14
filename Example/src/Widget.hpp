#pragma once

#include <list>
#include <chrono>

#include "Utilities.hpp"

#include "CordsPair.hpp"
#include "Event.hpp"
#include "Primitives.hpp"

class Window;

#define RAZOR_SHARK OnMove
#define FIRE_HOPPER OnClick
#define HOT_FIESTA OnTick
#define HAND_OF_MIDAS OnRelease

class Widget {
    protected:
        Widget* parent_;
        sf::RenderTexture widgetContainer_;

        uint32_t widgetColor_;
    private:
        int64_t width_;
        int64_t height_;

        uint32_t shiftX_;
        uint32_t shiftY_;

    protected:   
        bool isClicked_;
        bool isHolded_;
        bool isChanged_;
    public:
        Widget(uint32_t shiftX, uint32_t shiftY, int64_t width, int64_t height) :
        parent_(nullptr), 
        widgetContainer_(),
        widgetColor_(0xffffff00),
        width_(width), height_(height),
        shiftX_(shiftX), shiftY_(shiftY),
        isClicked_(0), isHolded_(0), isChanged_(1)
        {
            widgetContainer_.create(uint32_t(width_), uint32_t(height_));
        }

        virtual ~Widget() {}

        Widget& operator=([[maybe_unused]] const Widget& widgToCpy) = default;
        Widget(const Widget& widgToCpy) = default;

        virtual void RAZOR_SHARK([[maybe_unused]] const Event& curEvent) {

        }

        virtual void FlagClicked(const CordsPair& cords) {
            if (IsClicked(cords)) {
                isClicked_ = 1;
            }
        }

        virtual bool IsClicked(const CordsPair& cords) = 0;

        bool GetClickedState() {
            return isClicked_;
        }

        void SetClickedState(const bool newState) {
            isClicked_ = newState;
        }

        virtual void FlagHolded(const CordsPair& cords) {
            if (isClicked_ && IsClicked(cords)) {
                isHolded_ = 1;
            }
        }

        virtual void FIRE_HOPPER(const Event& curEvent) {
            CordsPair curCords = {curEvent.Oleg_.mbedata.x, curEvent.Oleg_.mbedata.y};

            FlagClicked(curCords);
            FlagHolded(curCords);
        }

        virtual void ReDraw() = 0;

        sf::RenderTexture& GetRenderTexture() {
            return widgetContainer_;
        }

        virtual void ProcessRedraw() {
            if (isChanged_) {
                widgetContainer_.clear();
                ReDraw();

                isChanged_ = 0;
            }
        }

        virtual void PlaceTexture() {
            sf::Sprite sprite(widgetContainer_.getTexture());
            sprite.setPosition({float(shiftX_), float(shiftY_)});

            parent_->GetRenderTexture().draw(sprite);
            parent_->GetRenderTexture().display();
        }

        virtual void HOT_FIESTA([[maybe_unused]] const Event& curEvent) {
            ProcessRedraw();
            PlaceTexture();
        }

        virtual void FlagReleased() {
            isClicked_ = 0;
            isHolded_  = 0;

            SetChanged();
        }

        virtual void HAND_OF_MIDAS([[maybe_unused]] const Event& curEvent) {
            FlagReleased();
        }

        virtual void OnKeyboard([[maybe_unused]] const Event& curEvent) {

        }

        virtual Widget* GetParent() {
            return parent_;
        }

        virtual void SetParent(Widget* newParent) {
            parent_ = newParent;
        }

        int64_t GetWidth() const {
            return width_;
        }

        int64_t GetHeight() const {
            return height_;
        }

        uint32_t GetShiftX() const {
            return shiftX_;
        }

        uint32_t GetShiftY() const {
            return shiftY_;
        }

        void SetChanged() {
            Widget* curWidget = this;

            while (curWidget) {
                curWidget->isChanged_ = 1;

                curWidget = curWidget->parent_;
            }
        }

        void SetSizes(const int64_t newWidth, const int64_t newHeight) {
            width_  = newWidth;
            height_ = newHeight;
            
            widgetContainer_.create(uint32_t(width_), uint32_t(height_));
            SetChanged();
        }

        void SetShifts(const uint32_t newXShift, const uint32_t newYShift) {
            shiftX_ = newXShift;
            shiftY_ = newYShift;

            SetChanged();
        }

        CordsPair ConvertXY(const CordsPair& cords) {
            Widget* curWidg = this;

            int32_t x = cords.x;
            int32_t y = cords.y;

            while (curWidg->parent_) {
                x += curWidg->shiftX_;
                y += curWidg->shiftY_;

                curWidg = curWidg->parent_;
            }

            return {x, y};
        }

        CordsPair ConvertRealXY(const CordsPair& cords) {
            std::list<Widget*> parentsList = {};

            for (Widget* curWidg = this; curWidg->parent_; curWidg = curWidg->parent_) {
                parentsList.push_front(curWidg);
            }

            int32_t x = cords.x;
            int32_t y = cords.y;

            for (auto& curWidg : parentsList) {
                x -= curWidg->shiftX_;
                y -= curWidg->shiftY_;
            }

            return {x, y};
        }
};

class ChildrenManager {
    private:
        std::list<Widget*> widgets_;

    public:
        ChildrenManager() :
        widgets_()
        {}

        ~ChildrenManager() {
            for (auto& curWidget : widgets_) {
                delete curWidget;
            }
        }

        void Clear() {
            for (auto& curWidget : widgets_) {
                delete curWidget;
            }

            widgets_.clear();
        }

        std::list<Widget*>* GetWidgetsList() {
            return &widgets_;
        }

        void operator+=(Widget* newWidget) {
            widgets_.push_back(newWidget);
        }

        void operator-=(Widget* widgetToClose) {
            for (auto it = widgets_.begin(); it != widgets_.end(); it++) {
                if (*it == widgetToClose) {
                    widgets_.erase(it);
                }
            }  
        }

        void TriggerMove(const Event& curEvent) {
            for (auto& curWidget : widgets_) {
                curWidget->OnMove(curEvent);
            }
        }

        void TriggerClick(const Event& curEvent) {
            for (auto& curWidget : widgets_) {
                curWidget->OnClick(curEvent);
            }
        }

        void TriggerTick(const Event& curEvent) {
            for (auto& curWidget : widgets_) {
                curWidget->OnTick(curEvent);
            }
        }

        void TriggerRelease(const Event& curEvent) {
            for (auto& curWidget : widgets_) {
                curWidget->OnRelease(curEvent);
            }
        }

        void TriggetKeyPressed(const Event& curEvent) {
            for (auto& curWidget : widgets_) {
                curWidget->OnKeyboard(curEvent);
            }
        }
};
