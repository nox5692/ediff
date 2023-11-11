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
class textComparator : public Comparator {
public:
    textComparator( const std::string &file_1, const std::string &file_2 );
    ~textComparator();
    /**
     * @brief Line by line exact text comparison method
     * 
     * Parses files side by side and checks lines that differ 
     * 
     * Respective overhaul of the UNIX diff command
     */
    void findDifferences() override;
    Output *formatDifference() const override;

private:
    std::ifstream _file_1;
    std::ifstream _file_2;
};
