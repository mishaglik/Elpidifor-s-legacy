/**
 * @file optionals.hpp
 * @author @mishaglik
 * @brief Standart optionals features.
 * @version 0.1
 * @date 2022-11-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef OPTIONALS_HPP
#define OPTIONALS_HPP

/**
 * @brief Here will be described standart optionals features, that will be wrapped with corresponding ifdef macroses.
 * Define it, and your plugin will REQUIRE this features by core application.
 * If your plugin can exist without this options, you can TRY to link to them with getLibSymbol, with guid = {} (Core app GUID);
 */

namespace booba {

#if defined(ELPIDIFOR_TEST_EXTENDED) or defined (ELPIDIFOR_ALL_EXTENIONS)
    /**
     * @brief This is function to test if extension is availiable.
     * Also it can be used to require extensions-supporting core.
     * @author @mishaglik
     * @return true. // It's ridiculous. I know it.
     */
    extern "C" bool testExtension();
#endif /* ELPIDIFOR_TEST_EXTENDED */

#if defined(ELPIDIFOR_HIDDEN_LAYER) or defined (ELPIDIFOR_ALL_EXTENIONS)
/**
 * @brief the hidden layer will be used to overlay temporary objects on the canvas, by the type of bounding
 * rectangles to highlight the area, the text insertion field, and so on. The hidden layer will be constantly rewritten on the main canvas
 * @return pointer on hidden layer image.
 */
extern "C" Image* getHiddenLayerID(); 
#endif /* ELPIDIFOR_HIDDEN_LAYER */


#if defined(ELPIDIFOR_CHECKBOX) or defined (ELPIDIFOR_ALL_EXTENIONS)
/**
 * @brief Checkbox is kind of button that keeps it's state.
 *
 * This function can only be called during buildSetupWidget();
 * Emits button clicked event with it's id when clicked.
 * @param x - x coordinate of new checkbox
 * @param y - y coordinate of new checkbox
 * @param w - width of new checkbox
 * @param h - height of new checkbox
 * @param text - text on checkbox.
 * @param start - initial state of checkbox
 * @return unique identifier. 0 if unsuccess.
 */
    extern "C" uint64_t createCheckbox(size_t x, size_t y, size_t w, size_t h, const char* text, bool start);

#endif /* ELPIDIFOR_CHECKBOX */

}
#endif /* OPTIONALS_HPP */
