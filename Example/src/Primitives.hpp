#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "tools.hpp"

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
            rect.setFillColor({color.red_, color.green_, color.blue_});

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

        virtual uint32_t getH() override {
            return height_;
        }

        virtual uint32_t getW() override {
            return width_;
        }

        virtual uint32_t getPixel(int32_t x, int32_t y) override {
            return GetPixel(x, y);
        }

        virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) override {
            SetPixel(x, y, color);
        }

        virtual uint32_t& operator()(uint32_t, uint32_t) override {
            return width_;
        }

        virtual const uint32_t& operator()(uint32_t, uint32_t) const override {
            return height_;
        }

        void SetPixel(uint32_t width, uint32_t height, const MyColor& color = 0) {
            realImage_.setPixel(width, height, {color.red_, color.green_, color.blue_});
        }

        uint32_t GetPixel(uint32_t width, uint32_t height) {
            return (uint32_t(realImage_.getPixel(width, height).r) << 24) + (uint32_t(realImage_.getPixel(width, height).g) << 16) + (uint32_t(realImage_.getPixel(width, height).b) << 8);
        }

        bool LoadFromFile(const sf::String& imageName) {
            return realImage_.loadFromFile(imageName);
        }   

        Image(uint32_t width, uint32_t height, const MyColor& color = 0) {
            width_  = width;
            height_ = height;

            realImage_.create(width, height, {color.red_, color.green_, color.blue_});
        }
        
        void Create(uint32_t width, uint32_t height, const uint8_t* pixels) {
            width_  = width;
            height_ = height;

            realImage_.create(width, height, pixels);
        }
        
        void Create(uint32_t width, uint32_t height, const MyColor& color = 0) {
            width_  = width;
            height_ = height;

            realImage_.create(width, height, {color.red_, color.green_, color.blue_});
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
};
