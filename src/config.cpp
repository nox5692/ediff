#include "config.h"

/**
 * @brief Codes for compTypes
 *
 * 0 - bin
 * 1 - txt
 * 2 - txt (ignore whitespace)
 * 3 - txt (word histogram)
 * 4 - css
 * 5 - img
 *
 * 6 - dir (names)
 * 7 - dir (contents)
 */

std::map<std::string, size_t> VALID_ARGUMENTS = {
    { "-bin", 0 }, { "-txt", 1 }, { "-css", 4 }, { "-png", 5 } };
std::map<std::string, size_t> VALID_TEXT_OPTIONS = { { "-w", 2 }, { "-h", 3 } };
std::map<std::string, size_t> VALID_DIRECTORY_OPTIONS = { { "-names", 6 }, { "-contents", 7 } };
std::set<std::string> VALID_AUTO_SUFFIX = { ".txt", ".bin", ".css", ".png" };
std::set<char> WORD_DELIMETERS = { '.', ',', ';', ':', '(', ')', '[', ']',
                                   '{', '}', '?', '!', '/', '<', '>' };

bool isDelim( const char c ) {
    return WORD_DELIMETERS.count( c ) > 0;
}
