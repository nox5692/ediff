#include <cctype>
#include <cstring>
#include <iterator>
#include <string>

#include "textWhitespaceComparator.h"

textWhitespaceComparator::textWhitespaceComparator( const std::string &file_1,
                                                    const std::string &file_2 )
    : Comparator( file_1, file_2 ), _file_1( file_1 ), _file_2( file_2 ) {
    // 1, 2, 3
}

textWhitespaceComparator::~textWhitespaceComparator() {
    if ( _file_1.is_open() )
        _file_1.close();
    if ( _file_2.is_open() )
        _file_2.close();
}

void textWhitespaceComparator::findDifferences() {

    std::string buffer_1( CHAR_BUFFER_LENGTH, 0 );
    std::string buffer_2( CHAR_BUFFER_LENGTH, 0 );

    while ( true ) {
        size_t count_1 = 0;
        size_t count_2 = 0;
        buffer_1.clear();
        buffer_2.clear();

        // Loads buffers
        while ( count_1 < CHAR_BUFFER_LENGTH && !_file_1.eof() ) {
            char c;
            _file_1.get( c );
            if ( _file_1.eof() )
                break;
            if ( !std::isspace( c ) ) {
                buffer_1 += c;
                count_1++;
            }
        }

        while ( count_2 < CHAR_BUFFER_LENGTH && !_file_2.eof() ) {
            char c;
            _file_2.get( c );
            if ( _file_2.eof() )
                break;
            if ( !std::isspace( c ) ) {
                buffer_2 += c;
                count_2++;
            }
        }
        if ( count_1 != count_2 )
            break;
        for ( size_t i = 0; i < count_1; i++ )
            if ( buffer_1.at( i ) != buffer_2.at( i ) )
                if ( notFull() ) {
                    _diff_count++;
                    _differences.push_back( new TextWhitespaceDifference( buffer_1.at( i ), buffer_2.at( i ), i ) );
                }

        if ( _file_1.eof() || _file_2.eof() )
            break;
    }
}

Output *textWhitespaceComparator::formatDifference() const {
    return new FileOutput( _differences, _diff_count );
}