#pragma once

/**
 * @file textComparator.h
 * @author Dan Vychytil (vychydan@fit.cvut.cz)
 * @brief Declaration of the textComparator class, which is a child class of Comparator.
 * @date 2023-05-10
 */

#include <fstream>
#include <vector>

#include "comparator.h"
#include "output.h"

/**
 * @brief Compares two text files
 *
 * Should be able to comapre files
 */
class textHistogramComparator : public Comparator {
public:
    textHistogramComparator( const std::string &file_1, const std::string &file_2 );
    ~textHistogramComparator();
    
    /**
     * @brief Parses files and c ounts individual words.
     * 
     * Is non-case sensitiive and does not account for delimeters (config.h)
     * 
     */
    void findDifferences() override;
    Output *formatDifference() const override;

private:
    std::ifstream _file_1;
    std::ifstream _file_2;
};