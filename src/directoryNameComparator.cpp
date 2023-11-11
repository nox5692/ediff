#include <algorithm>

#include "directoryNameComparator.h"

namespace fs = std::filesystem;

directoryNameComparator::directoryNameComparator( const std::string &directory_1,
                                                  const std::string &directory_2 )
    : Comparator( directory_1, directory_2 ) {
    std::vector<std::string> contents_1;
    std::vector<std::string> contents_2;
    for ( const auto &file : fs::directory_iterator( _name_1 ) )
        contents_1.push_back( file.path().filename().string() ); // Can be file or directory
    for ( const auto &file : fs::directory_iterator( _name_2 ) )
        contents_2.push_back( file.path().filename().string() );
    _directory_1 = std::make_pair( _name_1, contents_1 );
    _directory_2 = std::make_pair( _name_2, contents_2 );
}

void directoryNameComparator::findDifferences() {
    std::vector<std::string> unique_1;
    std::vector<std::string> unique_2;

    for ( auto it = _directory_1.second.begin(); it != _directory_1.second.end(); it++ ) {
        auto match_it = std::find( _directory_2.second.begin(), _directory_2.second.end(), *it );
        if ( match_it == _directory_2.second.end() )
            if ( notFull() ) {
                _diff_count++;
                unique_1.push_back(*it);
            }
    }
    for ( auto it = _directory_2.second.begin(); it != _directory_2.second.end(); it++ ) {
        auto match_it = std::find( _directory_1.second.begin(), _directory_1.second.end(), *it );
        if ( match_it == _directory_1.second.end() )
            if ( notFull() ) {
                _diff_count++;
                unique_2.push_back(*it);
            }
    }
    // Only one difference is pushed because DirectoryNamesDifference holds 2 string std::vectors and thus handles all the values.
    if ( ! isSame() )
        _differences.push_back( new DirectoryNamesDifference( unique_1, unique_2 ) );

}

Output* directoryNameComparator::formatDifference() const {
    return new FileOutput( _differences ,_diff_count );
}