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
}
#endif /* OPTIONALS_HPP */
