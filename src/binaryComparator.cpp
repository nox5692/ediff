#include "binaryComparator.h"

#include <algorithm>
#include <bitset>

binaryComparator::binaryComparator( const std::string &file_1, const std::string &file_2 )
    : Comparator( file_1, file_2 ), _file_1( _name_1, std::ios::binary ),
      _file_2( _name_2, std::ios::binary ) {
    if ( !_file_1.is_open() )
        throw std::logic_error( "Error: " + _name_1 + " could not be opened." );
    if ( !_file_2.is_open() )
        throw std::logic_error( "Error: " + _name_2 + " could not be opened." );
}

binaryComparator::~binaryComparator() {
    if ( _file_1.is_open() )
        _file_1.close();
    if ( _file_2.is_open() )
        _file_2.close();
}

void binaryComparator::findDifferences() {
    size_t byte_count = 0;
    while ( true ) {
        std::vector<uint8_t> buffer_1( BYTE_BUFFER_LENGTH );
        std::vector<uint8_t> buffer_2( BYTE_BUFFER_LENGTH );
        _file_1.read( reinterpret_cast<char *>( buffer_1.data() ), BYTE_BUFFER_LENGTH );
        _file_2.read( reinterpret_cast<char *>( buffer_2.data() ), BYTE_BUFFER_LENGTH );
        size_t len_1 = _file_1.gcount();
        size_t len_2 = _file_2.gcount();

        size_t buff_len = std::min( len_1, len_2 );
        if ( buff_len == 0 )
            buff_len = std::max( len_1, len_2 );

        if ( buff_len == 0 )
            break;

        try {
            for ( size_t i = 0; i < buff_len; i++ ) {
                byte_count++;
                if ( buffer_1.at( i ) != buffer_2.at( i ) ) {
                    if ( notFull() ) {
                        _differences.push_back( new BinaryDifference(
                            buffer_1.at( i ), buffer_2.at( i ), byte_count ) );
                    }
                    _diff_count++;
                }
            }
        } catch ( std::out_of_range &error ) {
        }
    }
}

Output *binaryComparator::formatDifference() const {
    return new FileOutput( _differences, _diff_count );
}
