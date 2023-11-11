#include "directoryContentsComparator.h"

#include "application.h"
#include "binaryComparator.h"
#include "comparator.h"
#include "cssComparator.h"
#include "imageComparator.h"
#include "textComparator.h"
#include "textHistogramComparator.h"
#include "textWhitespaceComparator.h"

#include <ostream>
#include <string>

namespace fs = std::filesystem;

bool isFileAndDirectory( const std::string &path1, const std::string &path2 ) {
    bool isPath1File      = fs::is_regular_file( path1 );
    bool isPath1Directory = fs::is_directory( path1 );
    bool isPath2File      = fs::is_regular_file( path2 );
    bool isPath2Directory = fs::is_directory( path2 );

    return ( isPath1File && isPath2Directory ) ||
           ( isPath1Directory && isPath2File );
}

directoryContentsComparator::directoryContentsComparator(
    const std::string &directory_1, const std::string &directory_2 )
    : Comparator( directory_1, directory_2 ) {

    std::vector<std::string> contents_1;
    std::vector<std::string> contents_2;

    for ( const auto &file : fs::directory_iterator( _name_1 ) )
        contents_1.push_back(
            file.path().string() ); // Can be file or directory
    for ( const auto &file : fs::directory_iterator( _name_2 ) )
        contents_2.push_back( file.path().string() );

    _directory_1 = std::make_pair( _name_1, contents_1 );
    _directory_2 = std::make_pair( _name_2, contents_2 );
}

void directoryContentsComparator::findDifferences() {
    if ( _directory_1.second.size() != _directory_2.second.size() )
        _diff_count++;

    for ( auto item = _directory_1.second.begin();
          item != _directory_1.second.end(); item++ ) {
        bool found_counterpart = false;
        for ( auto counterpart = _directory_2.second.begin();
              counterpart != _directory_2.second.end(); counterpart++ ) {
            if ( isFileAndDirectory( *item, *counterpart ) )
                continue;
            // Manually 're-enter' console arguments to recursively start
            // another comparison process for the directory
            const char *items[] = { "ediff", "-contents", ( ( *item ).c_str() ),
                                    ( ( *counterpart ).c_str() ) };

            App app( 4, items );
            size_t comp_type;
            // By runnign getCompType() a directory comparator can be called
            // again

            try {
                comp_type = app.getCompType();
            } catch ( std::exception &error ) {
                comp_type = 0;
            }
            std::cout << comp_type << " ";

            Comparator *comparator = nullptr;
            comparator             = app.startComparison( comp_type );

            if ( comparator != nullptr ) {
                comparator->findDifferences();

                if ( comparator->isSame() ) {
                    std::cout << *item << " " << *counterpart << std::endl;
                    found_counterpart = true;
                    delete comparator;
                    _directory_2.second.erase( counterpart );
                    break;
                }

                delete comparator;
            }
        }

        if ( !found_counterpart )
            // This means that one or more files have not found any matches ->
            // directories are not equal
            _diff_count++;
    }
}

Output *directoryContentsComparator::formatDifference() const {
    return new DirectoryOutput( _differences, _diff_count );
}