#pragma once

#include <iostream>

/**
 * @brief Represents a RGBA representation of a single pixel color in a PNG image
 * 
 */
struct Color {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
    uint8_t _alpha;
    size_t _count; // For histogram comparison

    Color();
    Color( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha );

    /**
     * @brief Only compares RGBA and not _count
     * 
     */
    bool operator==( const Color &other ) const;

    /**
     * @brief Standaridized RGBA output
     * 
     */
    friend std::ostream &operator<<( std::ostream &out, const Color &color );
};