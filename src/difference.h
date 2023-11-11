#pragma once
/**
 * @file difference.h
 * @author Dan Vychytil
 * @brief Implementation of class representing
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "color.h"
#include "config.h"
#include "cssStyle.h"

/**
 * @brief Represents a difference accounted in a file vs file comparison.
 *
 * Held in the base Comparator class in a polymorphic vector -> all comparator styles can be easily
 * represented this way
 *
 */
class Difference {
public:
    Difference() {
    }
    virtual ~Difference() {
    }

    /**
     * @brief Virtual fuinction for displaying individual differences fro certain types and
     * scenarios.
     *
     * Output process is simply repeatedly calling this method for all elements in said _difference
     * std::vector of Comparator class
     *
     * @return std::string
     */
    virtual std::string print() const = 0;
};

class BinaryDifference : public Difference {
public:
    BinaryDifference( const std::bitset<8> &byte_1, const std::bitset<8> &byte_2,
                      const size_t byte_number );
    std::string print() const override;

private:
    std::bitset<8> _byte_1;
    std::bitset<8> _byte_2;
    size_t _byte_num;
};

class TextDifference : public Difference {
public:
    TextDifference( const std::string &line_1, const std::string &line_2,
                    const size_t line_number );
    std::string print() const override;

private:
    std::string _line_1;
    std::string _line_2;
    size_t _line_num;
};

class TextWhitespaceDifference : public Difference {
public:
    TextWhitespaceDifference( const char &char_1, const char &char_2, const size_t char_number );
    std::string print() const override;

private:
    char _char_1;
    char _char_2;
    size_t _char_num;
};

class TextHistogramDifference : public Difference {
public:
    TextHistogramDifference( const std::string &word_1, const size_t word_count_1,
                             const size_t word_count_2 );
    std::string print() const override;

private:
    std::string _word;
    size_t _word_count_1;
    size_t _word_count_2;
};

class ImageDifference : public Difference {
public:
    ImageDifference( const Color &color_1, const Color &color_2 );
    std::string print() const override;

private:
    Color _pixel_color_1;
    Color _pixel_color_2;
};

class CSSDifference : public Difference {
public:
    CSSDifference( const std::string &name, const Selector &selector_1,
                   const Selector &selector_2 );
    std::string print() const override;

private:
    std::string _name;
    Selector _selector_1;
    Selector _selector_2;
};

class DirectoryNamesDifference : public Difference {
public:
    DirectoryNamesDifference( const std::vector<std::string> &items_1,
                              const std::vector<std::string> &items_2 );
    std::string print() const override;

private:
    std::vector<std::string> _uniq_items_1;
    std::vector<std::string> _uniq_items_2;
};