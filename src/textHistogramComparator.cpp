#include <cctype>
#include <cstring>
#include <iterator>
#include <string>

#include "textHistogramComparator.h"

textHistogramComparator::textHistogramComparator( const std::string &file_1,
                                                  const std::string &file_2 )
    : Comparator( file_1, file_2 ), _file_1( file_1 ), _file_2( file_2 ) {
    // 1, 2, 3
}

textHistogramComparator::~textHistogramComparator() {
    if ( _file_1.is_open() )
        _file_1.close();
    if ( _file_2.is_open() )
        _file_2.close();
}

void textHistogramComparator::findDifferences() {
    std::map<std::string, size_t> _contents_1;
    std::map<std::string, size_t> _contents_2;

    while ( true ) {
        std::istream_iterator<std::string> it_1( _file_1 );
        std::istream_iterator<std::string> it_2( _file_2 );
        // When istream_iterator finishes it returns to the start
        std::istream_iterator<std::string> end;

        while ( it_1 != end ) {
            std::string word = *it_1;
            size_t word_pos = 0;

            for ( auto c = word.begin(); c != word.end(); ) {
                if ( isDelim( *c ) ) {
                    word.erase( word_pos, 1 );
                } else {
                    *c = toupper( *c );
                    c++; // Iteration only moves when character is valid
                    word_pos++;
                }
            }
            _contents_1[word]++;
            it_1++;
        }

        while ( it_2 != end ) {
            std::string word = *it_2;
            size_t word_pos = 0;

            for ( auto c = word.begin(); c != word.end(); ) {
                if ( isDelim( *c ) ) {
                    word.erase( word_pos, 1 );
                } else {
                    *c = toupper( *c );
                    c++;
                    word_pos++;
                }
            }
            _contents_2[word]++;
            it_2++;
        }

        if ( _file_1.eof() )
            break;
    }

    // Update _contents_2 with words from _contents_1
    for ( const auto &word : _contents_1 ) {
        if ( _contents_2.count( word.first ) == 0 ) {
            _contents_2[word.first] = 0; // Add the word to _contents_2 with count 0
        }
    }

    // Update _contents_1 with words from _contents_2
    for ( const auto &word : _contents_2 ) {
        if ( _contents_1.count( word.first ) == 0 ) {
            _contents_1[word.first] = 0; // Add the word to _contents_1 with count 0
        }
    }

    for ( const auto &diff : _contents_1 ) {
        if ( diff.second != _contents_2.at( diff.first ) ) {
            if ( notFull() ) {
                std::string name = diff.first;
                size_t count_1 = diff.second;
                size_t count_2 = _contents_2[name];
                _diff_count++;
                _differences.push_back( new TextHistogramDifference( name, count_1, count_2 ) );
            }
        }
    }
}

Output *textHistogramComparator::formatDifference() const {
    return new FileOutput( _differences, _diff_count );
}