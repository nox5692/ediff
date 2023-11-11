#pragma once

/**
 * @file config.h
 * @author your name (you@domain.com)
 * @brief File with predefined constants and function sused frequently in this project.
 * Changing these values may affect the performance and behaviour of this programme.
 * @version 0.1
 * @date 2023-06-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

// Value maps and sets of notable values
extern std::map<std::string, size_t> VALID_ARGUMENTS;
extern std::map<std::string, size_t> VALID_TEXT_OPTIONS;
extern std::map<std::string, size_t> VALID_DIRECTORY_OPTIONS;
extern std::set<std::string> VALID_AUTO_SUFFIX;
extern std::set<char> WORD_DELIMETERS;

// Helper functions
bool isDelim( const char c );

// Size caps
constexpr size_t BYTE_BUFFER_LENGTH = 2048; // Max byte buffer size for byte by byte comparison
constexpr size_t CHAR_BUFFER_LENGTH = 2048; // Max char buffer size for byte by byte comparison
constexpr size_t TEXT_BUFFER_LENGTH = 200;  // Max word buffer count for text fomparison
constexpr size_t MAX_DIFFERENCES = 40;      // Max differences to be outputted after comparison

// ANSI Colors
constexpr char COLOR_RED[] = "\x1b[31m";
constexpr char COLOR_GREEN[] = "\x1b[32m";
constexpr char COLOR_YELLOW[] = "\x1b[33m";
constexpr char COLOR_BLUE[] = "\x1b[34m";
constexpr char COLOR_MAGENTA[] = "\x1b[35m";
constexpr char COLOR_CYAN[] = "\x1b[36m";
constexpr char COLOR_RESET[] = "\x1b[0m";
