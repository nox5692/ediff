#pragma once

/**
 * @file binaryComparator.h
 * @author Dan Vychytil (vychydan@fit.cvut.cz)
 * @brief Declaration of the binaryComparator class, which is a child class of Comparator.
 * @date 2023-05-10
 */

#include <bitset>
#include <fstream>
#include <fstream>

#include "comparator.h"
#include "output.h"

/**
 * @brief Compares two binary files by single bytes.
 *
 */
class binaryComparator : public Comparator {
public:
    binaryComparator( const std::string &file_1, const std::string &file_2 );
    ~binaryComparator();
    /**
     * @brief Byte by byte comparison of a binary file
     * 
     * Using fixed width integer type to make comparison easier
     */
    void findDifferences() override;
    Output *formatDifference() const override;

private:
    std::ifstream _file_1;
    std::ifstream _file_2;
};