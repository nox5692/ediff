#pragma once

#include <filesystem>
#include <vector>

#include "comparator.h"
#include "output.h"

namespace fs = std::filesystem;
/**
 * @brief Used for basic name comparison of files in a directroy
 * 
 * Holds 2 pairs acting as the 'directory object'
 * 
 */
class directoryNameComparator : public Comparator {
public:
    directoryNameComparator( const std::string &directory_1, const std::string &directory_2 );
    /**
     * @brief Finds counterpart files/directories with the same name
     * 
     * Leftover files from each directory are then displayed as individual differences
     */
    void findDifferences() override;
    Output* formatDifference() const override;

private:
    std::pair<std::string, std::vector<std::string>> _directory_1;
    std::pair<std::string, std::vector<std::string>> _directory_2;
};