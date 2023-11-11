/**
 * @file main.cpp
 * @author Dan Vychytil (vychydan@fit.cvut.cz)
 * @brief Main file of
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 */

// For testing
#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>

// Runtime
#include "application.h" // Used for argument analysis and programme runtime coordination
#include "output.h"

// Comapratorts
#include "binaryComparator.h"
#include "comparator.h"
#include "config.h"
#include "cssComparator.h"
#include "directoryContentsComparator.h"
#include "directoryNameComparator.h"
#include "imageComparator.h"
#include "textComparator.h"
#include "textHistogramComparator.h"
#include "textWhitespaceComparator.h"

int main( int argument_count, char *arguments[] ) {

    App application( argument_count,
                     (const char **)arguments ); // Used for comparison type analysis
    size_t comp_type;                            // Code for the comparison type
    try {
        application.validArguments(
            argument_count );                  // Checks if programme executed with known arguments
        comp_type = application.getCompType(); // Figures out comparison type
    } catch ( const std::exception &error ) {
        std::cerr << error.what() << std::endl;
        application.inputError();
        return 1;
    }

    Comparator *comparator = nullptr;
    try {
        comparator = application.startComparison( comp_type );
    } catch ( const std::exception &error ) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    if ( comparator == nullptr ) {
        application.inputError();
        return 1;
    }

    try {
        comparator->findDifferences(); // File comparison is executed
    } catch ( const std::exception &error ) {
        std::cerr << error.what() << std::endl;
        delete comparator;
        return 1;
    }

    std::ostringstream oss; // Formatted buffer displaying differences
    Output *output = nullptr;
    output = comparator->formatDifference(); // Data from comparator used to construct output object

    output->run( oss ); // Formatted ostringstream dump
    std::cout << oss.str();

    // Memory deallocation
    delete output;
    delete comparator;
    return 0;
}
