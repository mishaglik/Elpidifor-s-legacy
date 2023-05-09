#ifndef TOOLS_HPP
#define TOOLS_HPP
/**
 * @file tools.hpp
 * @author First standart commitet.
 * @brief Basic plugin header.
 * @version 0.1.0a
 * @date 2022-11-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cstdint>
#ifdef ELPIDIFOR_STANDART_EXTENDED
#include "optionals.hpp"
#endif /* ELPIDIFOR_STANDART_EXTENDED */
#include <cstddef>
#include <algorithm>
#include <cassert>

namespace booba { // boot of outstanding best api

    /**
     * @brief GUID - global identifier of your plugin.
     *
     * @attention We use 4 version of GUID specified at @link http://www.rfc-editor.org/rfc/rfc4122 @endlink in it's string represenation.
     * @warning Null-terminated.
     * @warning GUID with all zero bytes reffers to core application.
     */
    struct GUID
    {
        char str[37];
    };

    /**
     * @brief We require you to implement this;
     * Only addTool and addFilter can be called in this function.
     */
    extern "C" void init_module();


    /**
     * @brief Returns GUID of this plugin.
     *
     * @return GUID of your plugin, which allows other plugins to use your symbols.
     */
    extern "C" GUID getGUID();

    enum class EventType
    {
        NoEvent        = 0, // Stub. Should be ignored.
        MouseMoved     = 1, // Mouse moved over image.  Data structure: MotionEventData
        MousePressed   = 2, // Mouse pressed on image.  Data structure: MouseButtonEventData
        MouseReleased  = 3, // Mouse released on image. Data structure: MouseButtonEventData

        ButtonClicked   = 4, // Button on toolbar was clicked. Data structure: ButtonClickedEventData.
        SliderMoved  = 5, // Slider on toolbar was moved. Data structure: SliderMovedEventData.
        CanvasMPressed  = 6, // Same as MousePressed, but on canvas. Data structure - CanvasEventData.
        CanvasMReleased = 7, // Same as MouseReleased, but on canvas. Data structure - CanvasEventData.
        CanvasMMoved    = 8, // Same as MouseMoved, but on canvas. Data structure - CanvasEventData.
        MouseLeft       = 9, // Mouse left image. Data structure - None;

        TimerEvent      = 10, // Timer event. Data structure - TimerEventData.
        TextEvent       = 11, // Text changed event. Data structure - TextEventData.
    };

    enum class MouseButton
    {
        Left,
        Right
    };

    struct MotionEventData
    {
        size_t x, y;
        /**
         * @brief Relative to previous mouse position.
         */
        int64_t rel_x, rel_y;
    };

    struct MouseButtonEventData
    {
        size_t x, y;
        MouseButton button;
        /**
         * @brief If corresponding keys was pressed.
         */
        bool shift, alt, ctrl;
    };

    struct ButtonClickedEventData
    {
        /**
         * @brief Id of button.
         */
        uint64_t id;
    };

    struct SliderMovedEventData
    {
        /**
         * @brief Id of slider.
         */
        uint64_t id;
        int64_t value;
    };


    struct CanvasEventData
    {
        /**
         * @brief Id of Canvas.
         */
        uint64_t id;
        size_t x, y;
    };

    struct TimerEventData
    {
        /**
         * @brief time in ms counting from the start of thr program.
         */
        uint64_t time;
    };

    struct TextEventData
    {
        /**
         * @brief Id of Text.
         */
        uint64_t id;
        const char *text;
    };


    /**
     * @brief booba::Event is used to transmit event inside plugin.
     */
    class Event
    {
    public:
        EventType type;
        union
        {
            MotionEventData motion;
            MouseButtonEventData mbedata;
            ButtonClickedEventData bcedata;
            SliderMovedEventData smedata;
            CanvasEventData cedata;
            TimerEventData tedata;
            TextEventData textdata;
        } Oleg; //Object loading event group.
    };

    class Color
    {
    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color (uint8_t r = 0u, uint8_t g = 0u, uint8_t b = 0u, uint8_t a = 255u):
            r(r), g(g), b(b), a(a) 
        {}

        Color(uint32_t integer):
            r(uint8_t(integer >> 24)),
            g(uint8_t(integer >> 16)),
            b(uint8_t(integer >> 8)),
            a(uint8_t(integer))
        {}
        
        uint32_t toInteger()
        {
            return (uint32_t(a) << 24) + (uint32_t(b) << 16) + (uint32_t(g) << 8) + uint32_t(r); 
        }

        bool operator ==(const Color &that) const
        {
            return r == that.r && g == that.g && b == that.b && a == that.a; 
        }
    };

    class Picture;
    
    class Image
    {
    public:
        /**
         * @brief Get height of image
         *
         * @return size_t - height of image.
         */
        virtual size_t getH()     = 0;

        /**
         * @brief Get width of image
         *
         * @return size_t - width of image
         */
        virtual size_t getW()     = 0;

        /**
         * @brief Get the Pixel object
         *
         * @param x - x coord. Must be less than width
         * @param y - y coord. Must be less than height
         * @return Color - color of pixel
         */
        virtual Color getPixel(size_t x, size_t y) = 0;

        /**
         * @brief Sets pixel on image.
         *
         * @param x - x coord. Must be less than width
         * @param y - y coord. Must be less than height
         * @param color - color of new pixel.
         */
        virtual void setPixel(size_t x, size_t y, Color color) = 0;

        /**
         * @brief Get picture - a rectangular pixel array.
         *
         * @note the rectangular must be in the images boundaries.
         *
         * @param x - x coord of left down corner
         * @param y - y coord of left down corner
         * @param h - height of the rectangular
         * @param w - width of the rectangular
         */
        virtual Picture getPicture(size_t x, size_t y, size_t h, size_t w) = 0;

        /**
         * @brief Set picture - a rectangular pixel array.
         *
         * @note the rectangular must be in the images boundaries.
         *
         * @param pic - the picture to set, move-only
         */
        virtual void setPicture(Picture &&pic) = 0;

        /**
         * @brief Get the Hidden Layer image, that allows to add some not persistant changes to the picture
         *
         * @return Image*, pointer can not be nullptr
         */
        virtual Image *getHiddenLayer() = 0;

    protected:
        ~Image() {}
    };

    /**
     * @brief Picture is an owning pixel array that copies rectangular picture
     *        from image on construction. It is move-only to stop unintentional
     *        copy.
     */
    class Picture {
    public:
        Picture(size_t x, size_t y, size_t w, size_t h, Color *image, size_t image_w, size_t image_h)
            : x(x), y(y), w(w), h(h)
        {
            assert(x + w <= image_w and y + h <= image_h);

            size_t size = w * h;
            data = new Color[size];
            for (size_t i = 0; i < h; ++i)
                std::copy(image + (i + y) * image_w + x,
                          image + (i + y) * image_w + x + w,
                          data + i * w);

        }

        Picture(Color *data, size_t x, size_t y, size_t w, size_t h, bool owning = true)
            : x(x), y(y), w(w), h(h), data(data), owning(owning) {}

        Picture(size_t x, size_t y, size_t w, size_t h, Image *image)
            : x(x), y(y), w(w), h(h)
        {
            size_t image_w = image->getW();
            size_t image_h = image->getH();
            assert(x + w <= image_w and y + h <= image_h);

            size_t size = w * h;
            data = new Color[size];
            for (size_t i = 0; i < w; ++i)
                for (size_t j = 0; j < h; ++j)
                    data[j * w + i] = image->getPixel(i + x, j + y);
        }


        Picture(const Picture &other) = delete;

        Picture(Picture &&other)
            : x(other.x), y(other.y), w(other.w), h(other.h), data(other.data)
        {
            other.x = other.y = -1;
            other.w = other.h = -1;
            other.data = nullptr;
        }

        void operator=(const Picture &other) = delete;

        void operator=(Picture &&other)
        {
            if (data != nullptr and owning)
                delete[] data;

            data = other.data;
            x = other.x;
            y = other.y;
            w = other.w;
            h = other.h;

            other.x = other.y = -1;
            other.w = other.h = -1;
            other.data = nullptr;
        }

        ~Picture()
        {
            if (data != nullptr and owning)
                delete[] data;

            x = y = -1;
            w = h = -1;
            data = nullptr;
        }

        Color& operator()(size_t x, size_t y)
        {
            assert(x < w and y < h);
            return data[y * w + x];
        }

        const Color& operator()(size_t x, size_t y) const
        {
            assert(x < w and y < h);
            return data[y * w + x];
        }

        void reshape(size_t new_x, size_t new_y, size_t new_w, size_t new_h)
        {
            if (new_x == -1)
                new_x = x;
            if (new_y == -1)
                new_y = y;
            if (new_w == -1)
                new_w = w;
            if (new_h == -1)
                new_h = h;

            assert(new_w * new_h == w * h);
            x = new_x;
            y = new_y;
            w = new_w;
            h = new_h;
        }

        Color* getData() const
        {
            return data;
        }

        Color* takeData()
        {
            auto ret = data;

            x = y = -1;
            w = h = -1;
            data = nullptr;

            return ret;
        }

        size_t getH() const
        {
            return h;
        }

        size_t getW() const
        {
            return w;
        }

        size_t getX() const
        {
            return x;
        }

        size_t getY() const
        {
            return y;
        }

    private:
        size_t x, y;
        size_t w, h;
        Color *data = nullptr;
        bool owning = true;
    };


    /**
     * @brief Drawing context.
     *
     */
    struct ApplicationContext
    {
        /**
         * @brief fgColor - foreground drawing color.
         * @brief bgColor - background drawing color.
         */
        Color fgColor, bgColor;
    };

    /**
     * @brief Abstract tool class.
     */
    class Tool
    {
    public:
        /**
         * @brief This function will be called on every event happens.
         *
         * @param image - Image to apply tool / filter. Can be nullptr. You shouldn't expect it to be valid after return
         * @param event - Event to proceed. Not nullptr.
         */
        virtual void apply(Image* image, const Event* event) = 0;

        /**
         * @brief Destroy the Tool object
         *
         */
        virtual ~Tool() {}

        /**
         * @brief Get the texture to draw.
         *
         * @return const char* - rel path to texture.
         */
        virtual const char* getTexture() = 0;

        /**
         * @brief Build widget on toolbar by using createButoon/createLabel/createSlider/createCanvas
         * They will be added to toolbar.
         */
        virtual void buildSetupWidget() = 0;
    };

    /**
     * @brief Function request toolBar width given size.
     * This function is called in buildSetupWidget() only before any creation of widgets.
     * If it is not called size of default toolbar is unspecified.
     * Call after creation of any widget is UB.
     * @return if creation was successfull.
     */
    extern "C" bool setToolBarSize(size_t w, size_t h);

    // This functions are implemented by GUI lib.
    // Core application MUST fit all next widgets is specified rects.
    /**
     * @brief Creates button on some given toolbar.
     * This function can only be called during buildSetupWidget();
     * Emits event with it's id when clicked.
     * @param x - x coordinate of new button
     * @param y - y coordinate of new button
     * @param w - width of new button
     * @param h - height of new button
     * @param text - text on button.
     * @return unique identifier. 0 if unsuccess.
     */
    extern "C" uint64_t createButton   (size_t x, size_t y, size_t w, size_t h, const char* text);

    /**
     * @brief Creates label on some given toolbar.
     * This function can only be called during buildSetupWidget();
     * @param x - x coordinate of new label
     * @param y - y coordinate of new label
     * @param w - width of new label
     * @param h - height of new label
     * @param text - text on label.
     * @return unique identifier. 0 if unsuccess.
     */
    extern "C" uint64_t createLabel    (size_t x, size_t y, size_t w, size_t h, const char* text);

    /**
     * @brief Creates slider on some given toolbar.
     * This function can only be called during buildSetupWidget();
     * Emits event with it's id when value changed.
     * @param x - x coordinate of new slider
     * @param y - y coordinate of new slider
     * @param w - width of new slider
     * @param h - height of new slider
     * @param maxValue - maximum value of slider.
     * @param startvalue - start value of slider.
     * @return unique identifier. 0 if unsuccess.
     */
    extern "C" uint64_t createSlider(size_t x, size_t y, size_t w, size_t h, int64_t minValue, int64_t maxValue, int64_t startValue);

    /**
     * @brief Set value to slider by id sliderId.
     */
    extern "C" void setValueSlider(uint64_t sliderId, int64_t value);

    /**
     * @brief Creates editor on some given toolbar.
     * This function can only be called during buildSetupWidget();
     * Emits event with it's id when clicked.
     * @param x - x coordinate of new editor
     * @param y - y coordinate of new editor
     * @param w - width of new editor
     * @param h - height of new editor
     * @return unique identifier. 0 if unsuccess.
     */
    extern "C" uint64_t createEditor   (size_t x, size_t y, size_t w, size_t h);

    /**
     * @brief Set text to editor with id editorId.
     */
    extern "C" void setTextEditor(uint64_t editorId, const char *text);

    /**
     * @brief Get text from editor with id editorId.
     */
    extern "C" char* getTextEditor(uint64_t editorId);

    /**
     * @brief set text to label wtih id labelID
     */
    extern "C" void setTextLabel(uint64_t labelId, const char *text);
    
    /**
     * @brief get text from label with id labelId
     */
    extern "C" char* getTextLabel(uint64_t labelId);

    /**
     * @brief Creates canvas on some given toolbar.
     * This function can only be called during buildSetupWidget();
     * @param x - x coordinate of new canvas
     * @param y - y coordinate of new canvas
     * @param w - width of new canvas
     * @param h - height of new canvas
     * @return unique identifier. 0 if unsuccess.
     */
    extern "C" uint64_t createCanvas(size_t x, size_t y, size_t w, size_t h);

    /**
     * @brief Puts pixel to canvas with given id
     * @param canvas - id of canvas, returned by createCanvas
     * @param x - x coordinate of pixel.
     * @param y - y coordinate of pixel.
     * @param color - color of pixel.
     */
    extern "C" void putPixel (uint64_t canvas, size_t x, size_t y, Color color);

    /**
     * @brief Blits image to canvas
     * @param canvas - id of canvas, returned by createCanvas
     * @param x - x coordinate of sprite.
     * @param y - y coordinate of sprite.
     * @param w - width of image.
     * @param h - height of image.
     * @param texture - rel path to image.
     *
     */
    extern "C" void putSprite(uint64_t canvas, size_t x, size_t y, size_t w, size_t h, const char* texture);

     /**
     * @brief Cleans canvas with given id.
     * @param canvasId - id of canvas
     * @param color to clear.
     */
    extern "C" void cleanCanvas(uint64_t canvasId, Color color);

    /**
     * @brief Adds tool to application.
     * @param tool - tool pointer. App will delete it on exit itself.
     */
    extern "C" void addTool(Tool* tool);

   /**
     * @brief Adds filter to application.
     * May be different with addTool only by place whrere icon will be placed.
     * @param tool - tool pointer. App will delete it on exit itself.
     */
    extern "C" void addFilter(Tool* tool);


    /**
     * @brief Attempts to get symbol with name from plugin with given guid.
     * @param guid - GUID of plugin to take symbol.
     * @param name of symbol to perform lookup.
     * @return The address where that symbol is loaded into
       memory. nullptr if not found.
     */
    extern "C" void* getLibSymbol(GUID guid, const char* name);

    /**
     * @brief Pointer to ApplicationCotext.
     * Pointer itself should be not changed. But fields can be changed.
     */
    extern ApplicationContext* APPCONTEXT;
}

#endif /* TOOLS_HPP */
