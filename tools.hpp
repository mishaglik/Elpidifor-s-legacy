#ifndef TOOLS_HPP
#define TOOLS_HPP
/**
 * @file tools.hpp
 * @author First 
 * @brief 
 * @version 0.1
 * @date 2022-11-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
    Color is 0xRRGGBBAA
    Module name 
*/
#include <cstdint>
namespace booba {

    /**
     * @brief We require you to implement this;
     * 
     */
    void init_module();

    enum class EventType
    {
        NoEvent        = 0,
        MouseMoved     = 1,
        MousePressed   = 2,
        MouseReleased  = 3,

        ButtonClicked   = 4,
        ScrollbarMoved  = 5,
        CanvasMPressed  = 6,
        CanvasMReleased = 7,
        CanvasMMoved    = 8,

    };

    enum class MouseButton
    {
        Left,
        Right
    };

    struct Motion
    {
        int32_t x, y;
        int32_t rel_x, rel_y;
    };

    struct ButtonEData
    {
        int32_t x, y;
        bool shift, alt, ctrl;
    };

    class Event
    {
    public:
        EventType type;
        union 
        {
            Motion motion;
            ButtonEData data;
            // Button Scroll Canvas
        } Oleg; //Object loading event group.
    };


    class Image
    {
    public:
        virtual uint32_t getH()     = 0;
        virtual uint32_t getX()     = 0;
        virtual uint32_t getPixel() = 0;
        virtual void putPixel(uint32_t x, uint32_t y, uint32_t color) = 0;        
        virtual uint32_t& operator()(uint32_t x, uint32_t y);
        virtual const uint32_t& operator()(uint32_t x, uint32_t y) const;
    protected:
        virtual ~Image() = 0;
    };

    class Tool
    {
    public:
        virtual void apply(Image* image, const Event* event) = 0;
        virtual ~Tool() = 0;
        virtual const char* getTexture() = 0; 
        void buildSetupWidget();
    };

    extern uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char*);
    extern uint64_t createLabel    (int32_t x, int32_t y, uint32_t w, uint32_t h, const char*);
    extern uint64_t createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h);
    
    extern uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h);
    extern uint64_t putPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color);
    extern uint64_t putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture);
    

    // This function will be given to you;
    extern void addTool(Tool* tool);
}

#endif /* TOOLS_HPP */
