#include "output.h"

#include <vector>
#include <string>
#include <ostream>


Output::Output( const std::vector<Difference *> &diffs, const size_t count ) : _diff_count( count ) {
    for ( const auto &diff : diffs ) {
        if ( diff != nullptr ) {
            std::string diffString = diff->print(); // Get the string representation
            _out << diffString;                     // Write the string representation to 'out'
        }
    }
}


FileOutput::FileOutput( const std::vector<Difference *> &diffs, const size_t count )
    : Output( diffs, count ) {
}

void FileOutput::run( std::ostringstream &oss ) {
    oss << _out.str();
}


DirectoryOutput::DirectoryOutput( const std::vector<Difference *> &diffs, const size_t count )
    : Output( diffs, count ) {
}

void DirectoryOutput::run( std::ostringstream &oss ) {
    if ( _diff_count != 0 )
        oss << COLOR_RED << "Directories are not equal." << COLOR_RESET << std::endl;
}