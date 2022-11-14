#pragma once

#include <sstream>

#include "Window.hpp"

const int64_t XTextShift = 2;
const int64_t YTextShift = 2;

class Button : public Window {
    protected:
        BaseHandler<CordsPair>* clickAction_;

        MyColor hoveredColor_;
        MyColor clickedColor_;

        bool isHovered_;
    public:
        Button(uint32_t x, uint32_t y, uint32_t width, uint32_t height) :
        Window(x, y, width, height),
        clickAction_(nullptr),
        hoveredColor_(0x80808000), clickedColor_(0x9400d300),
        isHovered_(0)
        {   
            widgetColor_ = 0;
        }

        Button& operator=(const Button& button) = default;
        Button(const Button& button)            = default;

        virtual void MoveHover(const CordsPair& cords) {
            if (IsClicked(cords)) {
                isHovered_ = 1;

                SetChanged();
            }
            else if (isHovered_) {
                isHovered_ = 0;

                SetChanged();
            }
        }  

        virtual void OnMove(const Event& curEvent) override {
            Window::OnMove(curEvent);

            MoveHover({curEvent.Oleg_.motion.x, curEvent.Oleg_.motion.y});
        }

        void SetHandler(BaseHandler<CordsPair>* newHandler) {
            if (clickAction_) {
                delete clickAction_;
            }

            clickAction_ = newHandler;
        }

        virtual void FlagClicked(const CordsPair& cords) override {
            if (IsClicked(cords)) {
                isClicked_ = 1;

                SetChanged();
            }
        }

        virtual void OnClick(const Event& curEvent) override {
            Window::OnClick(curEvent);

            if (clickAction_) {
                clickAction_->Call({curEvent.Oleg_.mbedata.x, curEvent.Oleg_.mbedata.y});
            }
        }

        virtual void ReDraw() override {
            Rectangle realWindowRect({GetWidth(), GetHeight(), 0, 0, 0});

            MyColor curColor = 0;
            if (isClicked_) {
                curColor = clickedColor_;
            }
            else if (isHovered_) {
                curColor = hoveredColor_;
            }
            else {
                curColor = widgetColor_;
            }

            realWindowRect.Draw(widgetContainer_, curColor);  
        }
};
