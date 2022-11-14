#pragma once

#include "Widget.hpp"

class DynamicWindow;

class Window : public Widget {
    protected:
        ChildrenManager manager_;
    public:
        Window(uint32_t x, uint32_t y, uint32_t width, uint32_t height) :
        Widget(x, y, width, height),
        manager_()
        {}

        ~Window() {}

        void Clear() {
            manager_.Clear();
        }

        virtual void OnMove(const Event& curEvent) override {
            Widget::OnMove(curEvent);

            manager_.TriggerMove(curEvent);
        }

        virtual bool IsClicked(const CordsPair& vec) override {
            CordsPair realVec = ConvertRealXY(vec);

            return ((realVec.x >= 0)  && (realVec.x <= GetWidth()) && 
                    (realVec.y >= 0)  && (realVec.y <= GetHeight()));
        }

        virtual void OnClick(const Event& curEvent) override {
            Widget::OnClick(curEvent);

            manager_.TriggerClick(curEvent);
        }

        virtual void ReDraw() override {
            Rectangle realWindowRect({GetWidth(), GetHeight(), 0, 0, 0});

            realWindowRect.Draw(widgetContainer_, widgetColor_);  
        }

        virtual void OnTick(const Event& curEvent) override {
            ProcessRedraw();
            manager_.TriggerTick(curEvent);

            PlaceTexture();
        }

        virtual void OnRelease(const Event& curEvent) override {
            Widget::OnRelease(curEvent);

            manager_.TriggerRelease(curEvent);
        }

        virtual void OnKeyboard(const Event& curEvent) override {
            manager_.TriggetKeyPressed(curEvent);
        }

        virtual void operator+=(Widget* newWidget) {
            newWidget->SetParent(this);

            manager_ += newWidget;
        }

        void operator-=(Widget* widgetToDisconnect) {
            manager_ -= widgetToDisconnect;

            widgetToDisconnect->SetParent(nullptr);
        }


        virtual void SetParent(Widget* newParent) override {
            parent_ = newParent;

            for (auto& curChild : *manager_.GetWidgetsList()) {
                curChild->SetParent(this);
            }
        }
};

const int64_t TimeBetweenClicks = 30;
const int64_t TimeBetweenKeys   = 50;
const int64_t TimeBetweenTicks  = 10;

class RealWindow final : public Window {
    private:
        sf::RenderWindow realWindow_;

        int64_t lastPressedTime_;
        int64_t lastKeyPressedTime_;
        int64_t lastReleasedTime_;
        int64_t lastTickTime_;
        int64_t lastMoveTime_;
    public:
        RealWindow(uint32_t width, uint32_t height) :
        Window(0, 0, width, height),
        realWindow_(sf::VideoMode(width, height), "Window"),
        lastPressedTime_(0), lastKeyPressedTime_(0), lastReleasedTime_(0), lastTickTime_(0), lastMoveTime_(0)
        {};

        ~RealWindow() {
            if (realWindow_.isOpen()) {
                realWindow_.close();
            }
        }

        virtual void PlaceTexture() override {
            sf::Sprite sprite(widgetContainer_.getTexture());
            sprite.setPosition({float(GetShiftX()), float(GetShiftY())});

            realWindow_.draw(sprite);
        }

        virtual bool IsClicked([[maybe_unused]] const CordsPair& vec) override {
            return true;
        }

        bool IsOpen() {
            return realWindow_.isOpen();
        }

        void Close() {
            realWindow_.close();
        }

        void Clear() {
            realWindow_.clear();
        }

        void Display() {
            realWindow_.display();
        }

        void PollEvent() {
            sf::Event curEvent;
            realWindow_.pollEvent(curEvent);

            Event myEvent(curEvent);

            switch (myEvent.type_) {
                case EventType::Closed: {
                    Close();

                    break;
                }

                case EventType::MouseMoved: {
                    if ((curEvent.mouseMove.y < 0) || (curEvent.mouseMove.y > GetHeight())) {
                        break;
                    }

                    OnMove(curEvent);

                    break;
                }

                case EventType::MousePressed: {
                    if ((GetTimeMiliseconds() - lastPressedTime_) < TimeBetweenClicks)
                        break;

                    OnClick(curEvent);

                    lastPressedTime_ = GetTimeMiliseconds();
                    break;
                }

                case EventType::MouseReleased: {
                    OnRelease(curEvent);

                    break;
                }

                case EventType::KeyPressed: {
                    OnKeyboard(curEvent);

                    break;
                }

                case EventType::NoEvent:
                case EventType::ButtonClicked:
                case EventType::ScrollbarMoved:
                case EventType::CanvasMPressed:
                case EventType::CanvasMReleased:
                case EventType::CanvasMMoved:
                default:
                    break;
            }

            OnTick(curEvent);
        }
};

class DynamicWindow : public Window {
    public:
        DynamicWindow(uint32_t x, uint32_t y) :
        Window(x, y, 0, 0)
        {}

        void operator+=(Widget* windowToAdd) override {
            windowToAdd->SetShifts(0, uint32_t(GetHeight()));
            SetSizes(std::max(GetWidth(), windowToAdd->GetWidth()), GetHeight() + windowToAdd->GetHeight());

            Window::operator+=(windowToAdd);
        }
};
