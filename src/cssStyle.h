#pragma once

/**
 * @file cssStyle.h
 * @author Dan Vychytil (vychydan@fit.cvut.cz)
 * @brief CSS Style implementation used in the cssComparator class
 *
 * Implements a class representing a CSS selector capable of collecting and holding it's styles.
 *
 * @date 2023-05-10
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * @brief Represents a single CSS style property.
 *
 * Is used in a pair with a style type indentifier. Also has the implemented '!important' priority
 * flag.
 */
struct Style {
    Style();
    Style( const std::string &value, const bool important );
    Style &operator=( const Style &other );
    friend bool operator==( const Style &a, const Style &b );
    friend bool operator!=( const Style &a, const Style &b );

    std::string _value;
    bool _important;
};

/**
 * @brief Represents a single HTML selector ( ID, className, ... ) with it's assigned style
 * properties represented in the 'Style' class.
 *
 */
struct Selector {
    Selector();
    Selector( const std::string &style_property, const Style &new_style );

    /**
     * @brief Adds/modifies a specific style property on a CSS Selector
     *
     * @param style_type The style property ( color, height, ... ) that is being added/modified
     * @param new_style New style value
     */
    void addStyle( const std::string &style_property, const Style &new_style );

    friend bool operator==( const Selector &a, const Selector &b );
    friend bool operator!=( const Selector &a, const Selector &b );

    std::map<std::string, Style> _styles;
};