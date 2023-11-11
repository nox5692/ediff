#include <cctype>
#include <cstring>
#include <iterator>
#include <string>

#include "textComparator.h"

textComparator::textComparator( const std::string &file_1, const std::string &file_2 )
    : Comparator( file_1, file_2 ), _file_1( file_1 ), _file_2( file_2 ) {
    // 1, 2, 3
}

textComparator::~textComparator() {
    if ( _file_1.is_open() )
        _file_1.close();
    if ( _file_2.is_open() )
        _file_2.close();
}

void textComparator::findDifferences() {
    std::string line_1;
    std::string line_2;
    size_t line_count = 0;
    while ( true ) {
        line_count++;
        std::getline( _file_1, line_1 );
        std::getline( _file_2, line_2 );
        if ( line_1 != line_2 ) {
            if ( notFull() ) {
                _diff_count++;
                _differences.push_back( new TextDifference( line_1, line_2, line_count ) );
            }
        }
        if ( _file_1.eof() || _file_2.eof() )
            break;
    }
}

Output *textComparator::formatDifference() const {
    return new FileOutput( _differences, _diff_count );
}