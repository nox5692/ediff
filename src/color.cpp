#include "color.h"

Color::Color() {}

Color::Color( uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha ) : _red(red), _green(green), _blue(blue), _alpha(alpha), _count(0) {

}

bool Color::operator==( const Color &other ) const {
        return ( _red == other._red && _green == other._green && _blue == other._blue &&
                 _alpha == other._alpha );
}

std::ostream &operator<<( std::ostream &out, const Color &color ) {
    out << "RGB: (" << (size_t)color._red << ", " << (size_t)color._green << ", " << (size_t)color._blue << ", " << (size_t)color._alpha << ")" << std::endl;
    return out;
}