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
        CanvasMLeft     = 9, // Mouse left canvas.

        TimerEvent      = 10, // Timer event. Data structure - TimerEventData.
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
        } Oleg; //Object loading event group.
    };


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
         * @return uint32_t - color of pixel
         */
        virtual uint32_t getPixel(size_t x, size_t y) = 0;

        /**
         * @brief Sets pixel on image.
         * 
         * @param x - x coord. Must be less than width
         * @param y - y coord. Must be less than height
         * @param color - color of new pixel.
         */
        virtual void setPixel(size_t x, size_t y, uint32_t color) = 0;     
        
    protected:
        ~Image() {}
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
        uint32_t fgColor, bgColor;
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
    extern "C" void putPixel (uint64_t canvas, size_t x, size_t y, uint32_t color);
    
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
    extern "C" void cleanCanvas(uint64_t canvasId, uint32_t color);
    
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
