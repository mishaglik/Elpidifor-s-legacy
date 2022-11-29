#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <stack>
#include <filesystem>

#include <dlfcn.h>

#include "tools.hpp"

#include "Window.hpp"
#include "Button.hpp"

const char DefaultToolsPath[] = "./Plugins/";

class ImageWindow : public Window {
    public:
        Image image_;

        ImageWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height) :
        Window(x, y, width, height),
        image_(width, height)
        {

        }

        virtual void ReDraw() override {
            image_.rotation_ = 0;
            image_.Draw(widgetContainer_, {0, 0}, {0, 0}, uint32_t(GetWidth()), uint32_t(GetHeight()));
        }
};

