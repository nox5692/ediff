#pragma once

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "binaryComparator.h"
#include "comparator.h"
#include "config.h"
#include "cssComparator.h"
#include "directoryNameComparator.h"
#include "directoryContentsComparator.h"
#include "imageComparator.h"
#include "textComparator.h"
#include "textHistogramComparator.h"
#include "textWhitespaceComparator.h"

namespace fs = std::filesystem;

/**
 * @brief Controlls the flow of the whole process
 * 
 * Core object managing input arguments
 * 
 */
class App {
public:
    /**
     * @brief Analyzes argument string array
     *  
     * @param argument_count from main() arguments
     * @param arguments from main() arguments
     */
    App( int argument_count, const char *arguments[] );

    /**
     * @brief Checks if console arguments are known and valid
     *
     * @param argument_count
     */
    void validArguments( int argument_count ) const;

    /**
     * @brief Returns a value representing a certian comparison type
     *
     * @return
     */
    size_t getCompType();

    /**
     * @brief Get the suffix of a file (.txt, .png, ...)
     *
     * @return std::string
     */
    std::string getFileSuffix() const;

    /**
     * @brief Comparign files or directories?
     *
     * @return
     */
    int fileOrDirComp() const;

    /**
     * @brief Returns an instance of a new comparator object depending on the comparator type.
     *
     * @param compType The ID of the comparison type.
     * @return Comparator * - New instance of a Comparator sub-class.
     */
    Comparator *startComparison( const size_t &comp_type ) const;

    /**
     * @brief Serves as help/error for console input command
     * 
     */
    void inputError() const;

private:
    std::string _item_1;
    std::string _item_2;
    std::vector<std::string> _arguments;
};