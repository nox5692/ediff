#include "application.h"

namespace fs = std::filesystem;

App::App( int argument_count, const char *arguments[] ) : _arguments( 0 ) {
    for ( size_t i = 1; i < (size_t)argument_count; i++ ) {
        if ( i + 2 == (size_t)argument_count )
            _item_1 = arguments[i];
        else if ( i + 1 == (size_t)argument_count )
            _item_2 = arguments[i];
        else
            _arguments.push_back( arguments[i] );
    }
}

void App::validArguments( int argument_count ) const {
    if ( argument_count < 3 || argument_count > 5 )
        throw std::logic_error( "Invalid number of arguments" );
}

size_t App::getCompType() {
    // Comparing files
    if ( fileOrDirComp() > 0 ) {
        if ( _arguments.empty() ) {
            // Compare by suffix
            std::string suffix = getFileSuffix();
            if ( VALID_AUTO_SUFFIX.count( suffix ) > 0 ) { // do files have a known suffix?
                suffix[0] = '-'; // Tranfortm suffix into console parameter (.txt -> -txt)
                // std::cout << suffix << std::endl;
                _arguments.push_back( suffix );
            } else {
                throw std::logic_error( "Ediff cannot figure out comparison type." );
            }
        }
        if ( _arguments[0] == "-txt" ) // Get explicit type of txt compare
            if ( _arguments.size() > 1 )
                return VALID_TEXT_OPTIONS[_arguments[1]];

        return VALID_ARGUMENTS[_arguments[0]];
    }
    // Comparing directories
    if ( fileOrDirComp() < 0 ) {
        if ( _arguments.empty() )
            throw std::logic_error( "Ediff cannot figure out directory comparison type." );
        if ( VALID_DIRECTORY_OPTIONS[_arguments[0]] == 0 )
            throw std::logic_error( "Invalid comparison type for directories." );
        return VALID_DIRECTORY_OPTIONS[_arguments[0]];
    }
    throw std::logic_error( "Cannot compare file to directory." );
    return 999;
}

std::string App::getFileSuffix() const {
    fs::path item_1( _item_1 );
    fs::path item_2( _item_2 );
    std::string suffix_1 = item_1.extension();
    std::string suffix_2 = item_2.extension();
    if ( suffix_1 == suffix_2 )
        return suffix_1;
    return std::string( "" );
}

int App::fileOrDirComp() const {
    fs::path item_1( _item_1 );
    fs::path item_2( _item_2 );
    if ( !fs::exists( item_1 ) || !fs::exists( item_2 ) )
        throw std::logic_error( "Invalid file/directories for comparison" );
    if ( fs::is_regular_file( item_1 ) && fs::is_regular_file( item_2 ) )
        return 1; // File
    if ( fs::is_directory( item_1 ) && fs::is_directory( item_2 ) )
        return -1; // Directory
    return 0;      // Invalid
}

Comparator *App::startComparison( const size_t &comp_type ) const {
    switch ( comp_type ) {
    case 0:
        return new binaryComparator( _item_1, _item_2 );
    case 1:
        return new textComparator( _item_1, _item_2 );
    case 2:
        return new textWhitespaceComparator( _item_1, _item_2 );
    case 3:
        return new textHistogramComparator( _item_1, _item_2 );
    case 4:
        return new cssComparator( _item_1, _item_2 );
    case 5:
        return new imageComparator( _item_1, _item_2 );
    case 6:
        return new directoryNameComparator( _item_1, _item_2 );
    case 7:
        return new directoryContentsComparator( _item_1, _item_2 );
    }
    return nullptr;
}

void App::inputError() const {
    std::cerr << "Usage: " << std::endl;
    std::cerr << "       "
              << "./ediff"
              << " [file1] [file2]" << std::endl;
    std::cerr << "       "
              << "./ediff"
              << " [compType] [option] [file1] [file2]" << std::endl;
    std::cerr << "[compType]: [-bin | -txt | -css]" << std::endl;
    std::cerr << "[option]:   [-w | -h] (text comparison only)" << std::endl << std::endl;
    std::cerr << "       "
              << "./ediff"
              << " [compType] [directory1] [directory2]" << std::endl;
    std::cerr << "[compType]: [-names | -contents]" << std::endl << std::endl;
}
