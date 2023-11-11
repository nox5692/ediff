#include "cssStyle.h"
// Implementation of Style member functions
Style::Style() : _value(), _important( false ) {
}

Style::Style( const std::string &value, const bool important )
    : _value( value ), _important( important ) {
}

Style &Style::operator=( const Style &other ) {
    _value = other._value;
    _important = other._important;
    return *this;
}

bool operator==( const Style &a, const Style &b ) {
    return ( a._value == b._value && a._important == b._important );
}

bool operator!=( const Style &a, const Style &b ) {
    return !( a == b );
}

// Implementation of Selector member functions
Selector::Selector() : _styles() {
}

Selector::Selector( const std::string &style_property, const Style &new_style ) {
    _styles.insert( std::make_pair( style_property, new_style ) );
}

void Selector::addStyle( const std::string &style_property, const Style &new_style ) {
    auto it = _styles.find( style_property );
    if ( it != _styles.end() ) {
        Style &existing_style = it->second;
        if ( !existing_style._important || new_style._important )
            existing_style = new_style;
    } else {
        _styles.insert( std::make_pair( style_property, new_style ) );
    }
}

bool operator==( const Selector &a, const Selector &b ) {
    if ( a._styles.size() != b._styles.size() )
        return false;
    for ( const auto &style : a._styles )
        if ( style.second != b._styles.at( style.first ) )
            return false;
    return true;
}

bool operator!=( const Selector &a, const Selector &b ) {
    return !( a == b );
}
