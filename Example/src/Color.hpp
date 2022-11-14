#pragma once

#include <iostream>
#include <cstdint>
#include <cmath>

class MyColor {
    public:
        uint8_t red_;
        uint8_t green_;
        uint8_t blue_;

        MyColor(uint32_t color) : 
        red_(uint8_t((color & 0xff000000) >> 24)), green_(uint8_t((color & 0x00ff0000) >> 16)), blue_(uint8_t((color & 0x0000ff00) >> 8))
        {

        }

        MyColor(uint8_t red, uint8_t green, uint8_t blue) :
        red_(red), green_(green), blue_(blue)
        {

        }

        operator uint32_t() const {
            return (uint32_t(red_) << 24u) + (uint32_t(green_) << 16u) + (uint32_t(blue_) << 8u);
        }
};