#include <cmath>
#include <iomanip>
#include <string>

#include "difference.h"

/**
 * Implementation of binaryDifference
 */

BinaryDifference::BinaryDifference( const std::bitset<8> &byte_1, const std::bitset<8> &byte_2,
                                    const size_t byte_number )
    : _byte_1( byte_1 ), _byte_2( byte_2 ), _byte_num( byte_number ) {
}

std::string BinaryDifference::print() const {
    std::ostringstream oss;
    oss << "Difference in byte #" << _byte_num << ": " << std::endl;
    oss << COLOR_RED << std::setw( 40 ) << "File 1: " << _byte_1 << COLOR_RESET << std::endl;
    oss << COLOR_GREEN << std::setw( 40 ) << "File 2: " << _byte_2 << COLOR_RESET << std::endl;
    oss << "\n--------------------------------------------------\n" << std::endl;
    return oss.str();
}

/**
 * Implementation of textDifferences
 *
 */

TextDifference::TextDifference( const std::string &line_1, const std::string &line_2,
                                const size_t line_number )
    : _line_1( line_1 ), _line_2( line_2 ), _line_num( line_number ) {
}

std::string TextDifference::print() const {
    std::ostringstream oss;
    oss << "Difference in line #" << _line_num << ": " << std::endl;
    oss << COLOR_RED << std::setw( 20 ) << "File 1: " << _line_1 << COLOR_RESET << std::endl;
    oss << COLOR_BLUE << std::setw( 20 ) << "File 2: " << _line_2 << COLOR_RESET << std::endl;
    oss << "\n--------------------------------------------------\n" << std::endl;
    return oss.str();
}

/**
 * Implementation of textHistogramDifferences
 *
 */

TextHistogramDifference::TextHistogramDifference( const std::string &word,
                                                  const size_t word_count_1,
                                                  const size_t word_count_2 )
    : _word( word ), _word_count_1( word_count_1 ), _word_count_2( word_count_2 ) {
}

std::string TextHistogramDifference::print() const {
    std::ostringstream oss;
    size_t total_count = _word_count_1 + _word_count_2;
    double prct_1 = static_cast<double>( _word_count_1 ) / total_count * 100.0;
    double prct_2 = static_cast<double>( _word_count_2 ) / total_count * 100.0;
    size_t bar_len_1 = static_cast<size_t>( prct_1 / 5.0 );
    size_t bar_len_2 = static_cast<size_t>( prct_2 / 5.0 );

    oss << "Word " << _word << ": " << std::endl;
    std::string histogram_1( bar_len_1, '#' );
    oss << COLOR_GREEN << std::setw( 30 ) << "In file 1: " << _word_count_1 << " - " << histogram_1
        << COLOR_RESET << std::endl;
    std::string histogram_2( bar_len_2, '#' );
    oss << COLOR_RED << std::setw( 30 ) << "In file 2: " << _word_count_2 << " - " << histogram_2
        << COLOR_RESET << std::endl;
    oss << "\n--------------------------------------------------\n" << std::endl;
    return oss.str();
}

/**
 * Implementation of textWhitespaceDifferences
 *
 */

TextWhitespaceDifference::TextWhitespaceDifference( const char &char_1, const char &char_2,
                                                    const size_t char_number )
    : _char_1( char_1 ), _char_2( char_2 ), _char_num( char_number ) {
}

std::string TextWhitespaceDifference ::print() const {
    std::ostringstream oss;
    oss << "Difference in char #" << _char_num << ": " << std::endl;
    oss << COLOR_RED << std::setw( 30 ) << "In file 1: " << _char_1 << COLOR_RESET << std::endl;
    oss << COLOR_GREEN << std::setw( 30 ) << "In file 2: " << _char_2 << COLOR_RESET << std::endl;
    return oss.str();
}

/**
 * Implementation of ImageDifferrence
 *
 *
 */

ImageDifference::ImageDifference( const Color &color_1, const Color &color_2 )
    : _pixel_color_1( color_1 ), _pixel_color_2( color_2 ) {
}

std::string ImageDifference::print() const {
    std::ostringstream oss;
    size_t total_count = _pixel_color_1._count + _pixel_color_2._count;
    double prct_1 = static_cast<double>( _pixel_color_1._count ) / total_count * 100.0;
    double prct_2 = static_cast<double>( _pixel_color_2._count ) / total_count * 100.0;
    size_t bar_len_1 = static_cast<size_t>( ( prct_1 / 100.0 ) * 20 );
    size_t bar_len_2 = static_cast<size_t>( ( prct_2 / 100.0 ) * 20 );

    oss << _pixel_color_1;
    std::string histogram_1( bar_len_1, '#' );
    oss << COLOR_RED << std::setw( 30 ) << "In file 1: " << _pixel_color_1._count << " - "
        << histogram_1 << COLOR_RESET << std::endl;
    std::string histogram_2( bar_len_2, '#' );
    oss << COLOR_GREEN << std::setw( 30 ) << "In file 2: " << _pixel_color_2._count << " - "
        << histogram_2 << COLOR_RESET << std::endl;

    oss << "\n--------------------------------------------------\n" << std::endl;
    return oss.str();
}

/**
 * Implementation of CSSDifferrence
 *
 */

CSSDifference::CSSDifference( const std::string &name, const Selector &selector_1,
                              const Selector &selector_2 )
    : _name( name ), _selector_1( selector_1 ), _selector_2( selector_2 ) {
}

std::string CSSDifference::print() const {
    std::ostringstream oss;
    oss << std::endl << "Difference in selector: " << COLOR_CYAN << '"' + _name + '"' << COLOR_RESET << " : "
        << std::endl;
    if ( _selector_1._styles.empty() )
        oss << COLOR_RED << std::setw( 20 ) << "-- null --" << COLOR_RESET << std::endl;
    for ( const auto &s : _selector_1._styles )
        oss << COLOR_RED << std::setw( 20 ) << s.first << ": " << s.second._value
            << ( s.second._important ? " !important" : "" ) << COLOR_RESET << std::endl;

    if ( _selector_2._styles.empty() )
        oss << COLOR_GREEN << std::setw( 20 ) << "-- null --" << COLOR_RESET << std::endl;
    for ( const auto &s : _selector_2._styles )
        oss << COLOR_GREEN << std::setw( 20 ) << s.first << ": " << s.second._value
            << ( s.second._important ? " !important" : "" ) << COLOR_RESET << std::endl;
    oss << "\n--------------------------------------------------\n";
    return oss.str();
}

DirectoryNamesDifference::DirectoryNamesDifference( const std::vector<std::string> &items_1,
                                                    const std::vector<std::string> &items_2 )
    : _uniq_items_1( items_1 ), _uniq_items_2( items_2 ) {
}

std::string DirectoryNamesDifference::print() const {
    std::ostringstream oss;
    oss << COLOR_GREEN << "Unique to directory 1: " << COLOR_RESET << std::endl;
    for ( const auto &name : _uniq_items_1 ) {
        oss << COLOR_GREEN << name << COLOR_RESET << std::endl;
    }
    oss << COLOR_RED << "Unique to directory 2: " << COLOR_RESET << std::endl;
    for ( const auto &name : _uniq_items_2 ) {
        oss << COLOR_RED << name << COLOR_RESET << std::endl;
    }
    return oss.str();
}