#include "cssComparator.h"

std::string stripSpaces( const std::string &str ) {
    std::string result;
    for ( char c : str ) {
        if ( c != ' ' ) {
            result += c;
        }
    }
    return result;
}

void stripImportant( std::string &str, const std::string &word ) {
    size_t word_pos = str.find( word );
    while ( word_pos != std::string::npos ) {
        str.erase( word_pos, word.length() );
        word_pos = str.find( word );
    }
}

// cssComparator

cssComparator::~cssComparator() {
    if ( _file_1.is_open() )
        _file_1.close();
    if ( _file_2.is_open() )
        _file_2.close();
}

void cssComparator::loadStyles( std::istream &file, std::map<std::string, Selector> &computed ) {
    while ( !file.eof() ) {
        std::string whole_selector, selector;
        char c;
        /**
         * Char by char, constructing a template of a CSS selector while keeping in mind different formatting styles
         * 
         * s. {
         *  style: val;
         * }
         * 
         * s. { style: val }
         * 
         * These and other formatting styles are supported, as long as they would not give an error to a CSS analyzer
         */
        while ( file.get( c ) && c != '}' ) {
            if ( c == '{' ) {
                // Selector ID is cut off by the {} style portion of the declaration
                selector = stripSpaces( whole_selector );
                whole_selector.clear();
            } else if ( c == ':' && !selector.empty() ) {
                std::string style_property = stripSpaces( whole_selector );
                whole_selector.clear();
                std::string style_value;

                // Checks for end of style value while keeping in mind CSS formatting conventions
                while ( file.get( c ) && c != ';' && c != '\n' && c != '}' )
                    if ( c != ' ' )
                        style_value += c;

                bool is_important = ( style_value.find( "!important" ) != std::string::npos );
                stripImportant( style_value, "!important" );
                Style new_style( style_value, is_important );

                // Adding individual styles to current selector being processed
                auto it = computed.find( selector );
                if ( it != computed.end() ) {
                    it->second.addStyle( style_property, new_style );
                } else {
                    Selector new_selector( style_property, new_style );
                    computed.insert( std::make_pair( selector, new_selector ) );
                }

            } else if ( c == ';' || c == '\n' ) {
                whole_selector.clear();
            } else {
                whole_selector += c;
            }
        }
    }
}

void cssComparator::findDifferences() {
    // Calling for individual file analysis
    loadStyles( _file_1, _computed_1 );
    loadStyles( _file_2, _computed_2 );

    // Check keys in _computed_1 and add missing keys to _computed_2
    for ( const auto &selector : _computed_1 ) {
        const std::string &key = selector.first;
        if ( _computed_2.find( key ) == _computed_2.end() )
            _computed_2.insert( std::make_pair( key, Selector() ) );
    }

    // Check keys in _computed_2 and add missing keys to _computed_1
    for ( const auto &selector : _computed_2 ) {
        const std::string &key = selector.first;
        if ( _computed_1.find( key ) == _computed_1.end() )
            _computed_1.insert( std::make_pair( key, Selector() ) );
    }

    // For all accounted calculated selectors, try and find a counterpart
    for ( const auto &selector : _computed_1 ) {
        if ( selector.second != _computed_2[selector.first] )
            if ( notFull() ) {
                _diff_count++;
                _differences.push_back( new CSSDifference( selector.first, selector.second,
                                                           _computed_2[selector.first] ) );
            }
    }
}

Output *cssComparator::formatDifference() const {
    return new FileOutput( _differences, _diff_count );
}