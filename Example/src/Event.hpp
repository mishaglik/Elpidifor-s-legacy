#pragma once

#include <SFML/Graphics.hpp>
#include <list>

enum class EventType {
    NoEvent        = 0,
    MouseMoved     = 1,
    MousePressed   = 2,
    MouseReleased  = 3,

    ButtonClicked   = 4,
    ScrollbarMoved  = 5,
    CanvasMPressed  = 6,
    CanvasMReleased = 7,
    CanvasMMoved    = 8,

    KeyPressed,
    Closed,
};

enum class MouseButton
{
    Left,
    Right
};

struct MotionEventData
{
    int32_t x, y;
    int32_t rel_x, rel_y;
};

struct MouseButtonEventData
{
    int32_t x, y;
    MouseButton button; 
    bool shift, alt, ctrl;
};

enum Key
{
    Unknown = -1, ///< Unhandled key
    A = 0,        ///< The A key
    B,            ///< The B key
    C,            ///< The C key
    D,            ///< The D key
    E,            ///< The E key
    F,            ///< The F key
    G,            ///< The G key
    H,            ///< The H key
    I,            ///< The I key
    J,            ///< The J key
    K,            ///< The K key
    L,            ///< The L key
    M,            ///< The M key
    N,            ///< The N key
    O,            ///< The O key
    P,            ///< The P key
    Q,            ///< The Q key
    R,            ///< The R key
    S,            ///< The S key
    T,            ///< The T key
    U,            ///< The U key
    V,            ///< The V key
    W,            ///< The W key
    X,            ///< The X key
    Y,            ///< The Y key
    Z,            ///< The Z key
    Num0,         ///< The 0 key
    Num1,         ///< The 1 key
    Num2,         ///< The 2 key
    Num3,         ///< The 3 key
    Num4,         ///< The 4 key
    Num5,         ///< The 5 key
    Num6,         ///< The 6 key
    Num7,         ///< The 7 key
    Num8,         ///< The 8 key
    Num9,         ///< The 9 key
    Escape,       ///< The Escape key
    LControl,     ///< The left Control key
    LShift,       ///< The left Shift key
    LAlt,         ///< The left Alt key
    LSystem,      ///< The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
    RControl,     ///< The right Control key
    RShift,       ///< The right Shift key
    RAlt,         ///< The right Alt key
    RSystem,      ///< The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
    Menu,         ///< The Menu key
    LBracket,     ///< The [ key
    RBracket,     ///< The ] key
    Semicolon,    ///< The ; key
    Comma,        ///< The , key
    Period,       ///< The . key
    Quote,        ///< The ' key
    Slash,        ///< The / key
    Backslash,    ///< The \ key
    Tilde,        ///< The ~ key
    Equal,        ///< The = key
    Hyphen,       ///< The - key (hyphen)
    Space,        ///< The Space key
    Enter,        ///< The Enter/Return keys
    Backspace,    ///< The Backspace key
    Tab,          ///< The Tabulation key
    PageUp,       ///< The Page up key
    PageDown,     ///< The Page down key
    End,          ///< The End key
    Home,         ///< The Home key
    Insert,       ///< The Insert key
    Delete,       ///< The Delete key
    Add,          ///< The + key
    Subtract,     ///< The - key (minus, usually from numpad)
    Multiply,     ///< The * key
    Divide,       ///< The / key
    Left,         ///< Left arrow
    Right,        ///< Right arrow
    Up,           ///< Up arrow
    Down,         ///< Down arrow
    Numpad0,      ///< The numpad 0 key
    Numpad1,      ///< The numpad 1 key
    Numpad2,      ///< The numpad 2 key
    Numpad3,      ///< The numpad 3 key
    Numpad4,      ///< The numpad 4 key
    Numpad5,      ///< The numpad 5 key
    Numpad6,      ///< The numpad 6 key
    Numpad7,      ///< The numpad 7 key
    Numpad8,      ///< The numpad 8 key
    Numpad9,      ///< The numpad 9 key
    F1,           ///< The F1 key
    F2,           ///< The F2 key
    F3,           ///< The F3 key
    F4,           ///< The F4 key
    F5,           ///< The F5 key
    F6,           ///< The F6 key
    F7,           ///< The F7 key
    F8,           ///< The F8 key
    F9,           ///< The F9 key
    F10,          ///< The F10 key
    F11,          ///< The F11 key
    F12,          ///< The F12 key
    F13,          ///< The F13 key
    F14,          ///< The F14 key
    F15,          ///< The F15 key
    Pause,        ///< The Pause key

    KeyCount,     ///< Keep last -- the total number of keyboard keys
};

struct KeyPressedEventData
{
    Key code;
    bool shift, alt, ctrl;
};

struct ButtonClickedEventData
{
    uint64_t id; 
};

struct ScrollMovedEventData
{
    uint64_t id; 
    int32_t value;
};

struct CanvasEventData
{
    uint64_t id;
    int32_t x, y; 
};

class Event {
    public:
    EventType type_;

    union 
    {
        MotionEventData motion;
        MouseButtonEventData mbedata;
        ButtonClickedEventData bcedata;
        ScrollMovedEventData smedata;
        CanvasEventData cedata;
        KeyPressedEventData kpedata;
    } Oleg_; //Object loading event group.

    Event(const sf::Event& sfEvent) :
        type_(EventType::NoEvent),
        Oleg_({0, 0, 0, 0})
    {
        switch (sfEvent.type) {
            case sf::Event::Closed: {
                type_ = EventType::Closed;

                break;
            } 

            case sf::Event::MouseMoved: {
                type_ = EventType::MouseMoved;
                Oleg_.motion.x = sfEvent.mouseMove.x;
                Oleg_.motion.y = sfEvent.mouseMove.y;

                break;
            }

            case sf::Event::MouseButtonPressed: {
                type_ = EventType::MousePressed;

                if (sfEvent.mouseButton.button == sf::Mouse::Button::Left) {
                    Oleg_.mbedata.button = MouseButton::Left;
                }
                else if (sfEvent.mouseButton.button == sf::Mouse::Button::Right) {
                    Oleg_.mbedata.button = MouseButton::Right;
                }

                Oleg_.mbedata.x = sfEvent.mouseButton.x;
                Oleg_.mbedata.y = sfEvent.mouseButton.y;

                break;
            }

            case sf::Event::MouseButtonReleased: {
                type_ = EventType::MouseReleased;

                break;
            }

            case sf::Event::KeyPressed: {
                type_ = EventType::KeyPressed;

                Oleg_.kpedata.code = static_cast<Key>(sfEvent.key.code);
                
                if (sfEvent.key.alt) {
                    Oleg_.kpedata.alt = 1;
                }
                else if (sfEvent.key.control) {
                    Oleg_.kpedata.ctrl = 1;
                }
                else if (sfEvent.key.shift) {
                    Oleg_.kpedata.shift = 1;
                }

                break;
            }

            case sf::Event::Count:
            case sf::Event::Resized:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::TextEntered:
            case sf::Event::KeyReleased:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::JoystickMoved:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
            case sf::Event::SensorChanged:
            default:
                break;
        }
    }
};

template <class TArguments>
class BaseHandler {
    public:
        virtual void Call(const TArguments& args) = 0;

        virtual ~BaseHandler() {}
        BaseHandler() {}
    private:
};

template <class T, class TArguments>
class FuncCaller : public BaseHandler<TArguments> {
    public:
        FuncCaller(T* object, void (*callFunc)(T* obj, const TArguments& args)) :
        object_(object),
        callFunc_(callFunc)
        {}

        FuncCaller(const FuncCaller<T, TArguments>& toCpy) {
            object_   = toCpy.object_;
            callFunc_ = toCpy.callFunc_;
        }

        FuncCaller<T, TArguments>& operator=(const FuncCaller<T, TArguments>& toCpy) {
            object_   = toCpy.object_;
            callFunc_ = toCpy.callFunc_;
        }

        virtual void Call(const TArguments& args) override {
            callFunc_(object_, args);
        }

    private:
        T* object_;
        void (*callFunc_)(T* obj, const TArguments& args);
};

template <class T, class TArguments>
class MethodCaller : public BaseHandler<TArguments> {
        using TMethod = void (T::*)(const TArguments& args);

    public:
        MethodCaller(T* object, TMethod callMethod) :
        object_(object),
        callMethod_(callMethod)
        {}

        MethodCaller(const MethodCaller<T, TArguments>& toCpy) {
            object_   = toCpy.object_;
            callMethod_ = toCpy.callMethod_;
        }

        MethodCaller<T, TArguments>& operator=(const MethodCaller<T, TArguments>& toCpy) {
            object_     = toCpy.object_;
            callMethod_ = toCpy.callMethod_;
        }

        virtual void Call(const TArguments& args) override {
            (object_->*callMethod_)(args);
        }

    private:
        T* object_;
        TMethod callMethod_;
};

template <class T, class addT, class TArguments>
class AddMethodCaller : public BaseHandler<TArguments> {
        using TAddMethod = void (T::*)(addT* obj, const TArguments& args);

    public:
        AddMethodCaller(T* mainObject, addT* addObj, TAddMethod callMethod) :
        mainObject_(mainObject),
        addObject_(addObj),
        callMethod_(callMethod)
        {}

        AddMethodCaller(const AddMethodCaller<T, addT, TArguments>& toCpy) = default;
        AddMethodCaller<T, addT, TArguments>& operator=(const AddMethodCaller<T, addT, TArguments>& toCpy) = default;

        virtual void Call(const TArguments& args) override {
            (mainObject_->*callMethod_)(addObject_, args);
        }

    private:
        T* mainObject_;
        addT* addObject_;

        TAddMethod callMethod_;
};

// pimpl, компонентное программирование, Smalltalk, ECS - всё управляется сообщениями и подписками. 
