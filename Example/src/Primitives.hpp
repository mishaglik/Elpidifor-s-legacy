#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cassert>

#include "../../tools.hpp"

#include "CordsPair.hpp"
#include "Color.hpp"

const double TextScalar = 0.75;

class Rectangle {
    public:
        int64_t width_;
        int64_t height_;

        int64_t x_;
        int64_t y_;

        float rotation_ = 0;

        void Draw(sf::RenderTexture& widgetContainer, sf::Texture* texture) {
            sf::Vector2f sizesVec = {float(width_), float(height_)};
            sf::RectangleShape rect(sizesVec);

            rect.setPosition({float(x_), float(y_)});

            rect.setTexture(texture);

            widgetContainer.draw(rect);
            widgetContainer.display();
        }

        void Draw(sf::RenderTexture& widgetContainer, const MyColor& color) {
            sf::Vector2f sizesVec = {float(width_), float(height_)};
            sf::RectangleShape rect(sizesVec);

            rect.setPosition({float(x_), float(y_)});
            rect.setFillColor({color.r, color.g, color.b, color.a});

            widgetContainer.draw(rect);
            widgetContainer.display();
        }
};

class Image : public booba::Image {
    private:
        sf::Image realImage_ = {};
    public:
        uint32_t width_  = 0;
        uint32_t height_ = 0;

        float rotation_ = 0;

        Image *hidden_layer_;

        virtual ~Image() {}

        virtual size_t getH() override {
            return height_;
        }

        virtual size_t getW() override {
            return width_;
        }

        virtual booba::Color getPixel(size_t x, size_t y) override {
            return GetPixel(x, y);
        }

        virtual void setPixel(size_t x, size_t y, booba::Color color) override {
            SetPixel(x, y, MyColor(color.r, color.g, color.b, color.a));
        }

        virtual booba::Picture getPicture(size_t x, size_t y, size_t w, size_t h) override
        {
            assert(!"Not implemented yet");
        }

        virtual void setPicture(booba::Picture &&pic) override
        {
            assert(!"Not implemented yet");
        }

        void SetPixel(size_t width, size_t height, const MyColor& color = 0) {
            realImage_.setPixel(uint32_t(width), uint32_t(height), {color.r, color.g, color.b});
        }

        booba::Color GetPixel(size_t width, size_t height) {
            auto pixel = realImage_.getPixel(uint32_t(width), uint32_t(height));
            return pixel.toInteger();
        }

        bool LoadFromFile(const sf::String& imageName) {
            return realImage_.loadFromFile(imageName);
        }

        Image(uint32_t width, uint32_t height, const MyColor& color = 0) {
            width_  = width;
            height_ = height;

            realImage_.create(width, height, {color.r, color.g, color.b});
        }

        void Create(uint32_t width, uint32_t height, const uint8_t* pixels) {
            width_  = width;
            height_ = height;

            realImage_.create(width, height, pixels);
        }

        void Create(uint32_t width, uint32_t height, const MyColor& color = 0) {
            width_  = width;
            height_ = height;

            realImage_.create(width, height, {color.r, color.g, color.b});
        }

        void Clear() {
            for (uint32_t curX = 0; curX < width_; curX++) {
                for (uint32_t curY = 0; curY < height_; curY++) {
                    realImage_.setPixel(curX, curY, {0, 0, 0});
                }
            }
        }

        void Draw(sf::RenderTexture& container, const CordsPair& x0y0, const CordsPair& xyVirt, const uint32_t width, const uint32_t height) const {
            sf::Vector2f sizesVec = {float(width), float(height)};

            sf::RectangleShape rectangle(sizesVec);
            rectangle.setPosition({float(x0y0.x), float(x0y0.y)});

            sf::Texture curTexture = {};

            sf::IntRect area = {sf::Vector2i(xyVirt.x, xyVirt.y), sf::Vector2i(width, height)};

            curTexture.loadFromImage(realImage_, area);

            rectangle.setTexture(&curTexture);

            rectangle.setRotation(float((rotation_ / M_PI) * 180.0));

            container.draw(rectangle);
            container.display();
        }

        virtual booba::Image *getHiddenLayer() override
        {
            return hidden_layer_;
        }

        void clean(const booba::Color &color) override
        {

        }
};
