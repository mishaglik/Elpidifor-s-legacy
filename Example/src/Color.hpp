#pragma once

#include <iostream>
#include <cstdint>
#include <cmath>
#include "../../tools.hpp"

class MyColor : public booba::Color {
    public:

        MyColor(uint32_t color) : booba::Color(color)
        {}

        MyColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255): booba::Color(red, green, blue, alpha) {}
};