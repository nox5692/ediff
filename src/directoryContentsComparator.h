#pragma once

#include <filesystem>
#include <vector>
#include <algorithm>
#include <iostream>

#include "comparator.h"
#include "output.h"

namespace fs = std::filesystem;

/**
 * @brief Used for thorough directory comparison supporting recursive behavirou
 * 
 * Holds pairs representing individual 'directory objects'
 * 
 */
class directoryContentsComparator : public Comparator {
public:
    /**
     * @brief Performs a fs::path analysis and creates simplified std::pairs representing individual directories 
     */
    directoryContentsComparator( const std::string &directory_1, const std::string &directory_2 );
    /**
     * Utilizes the global App() class and matches custom comparison methods for all instances of a pair of directory items
     * 
     * If a specific comparison type cannot be igured out, the binaryComparator() is called as a safe measure.
     * 
     */
    void findDifferences() override;
    Output *formatDifference() const override;

private:
    std::pair<std::string, std::vector<std::string>> _directory_1;
    std::pair<std::string, std::vector<std::string>> _directory_2;
};