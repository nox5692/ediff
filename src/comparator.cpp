#include "comparator.h"

namespace fs = std::filesystem;

Comparator::~Comparator() {
    for ( auto class_ptr : _differences )
        delete class_ptr;
    _differences.clear();
}

bool Comparator::sameFileSize( const fs::path &a, const fs::path &b ) const {
    if ( fs::is_regular_file( a ) && fs::is_regular_file( b ) )
        return fs::file_size( a ) == fs::file_size( b );
    throw std::logic_error( "No valid files selected." );
    return false;
}

void Comparator::parseFile( std::istream &file ) {
}

bool Comparator::isSame() {
    return _diff_count == 0;
}

size_t Comparator::diffCount() {
    return _diff_count;
}

bool Comparator::notFull() {
    return _diff_count < 20;
}

