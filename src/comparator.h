#pragma once

/**
 * @file comparator.h
 * @author Dan Vychytil (vychydan@fit.cvut.cz)
 * @brief Icludes the declaration of the Comparator class
 * @date 2023-05-06
 */

#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "config.h"
#include "difference.h"
#include "output.h"

namespace fs = std::filesystem;

/**
 * @brief Virtual class representing a tool for comparing between two files/directories
 *
 */
class Comparator {
public:
    /**
     * @brief Construct a new Comparator object.
     *
     * Only saves the names of the two items, leaves item interpretation to the child classes.
     * Checks for file/directory validity.
     * @throw logic_error if comparison cannot proceed.
     *
     * @param item_1 The name of the first item to be compared.
     * @param item_2 The name of the second item to be compared.
     */
    Comparator( const std::string &item_1, const std::string &item_2 )
        : _name_1( item_1 ), _name_2( item_2 ), _diff_count( 0 ), _differences() {
    }

    /**
     * @brief Destroy the Comparator object
     *
     * Deallocates pointers in _differences and in certain instances closes ifstreams/FILEs after
     * the findDifferrences() method has been performed
     *
     */
    virtual ~Comparator();

    /**
     * @brief Parses files side by side and compares.
     *
     * Depending on comparison type, reads the contents and simoutenously writes notable
     * differences. For example: Line number where files differ. For directory comparison, calls
     * other Comparator classes if needed
     *
     * Has a limit set in the 'config.h' file for maximum differences to be saved, which is compared
     * to the '_diff_count' value, that is being updated while analyzing the file. This applies to
     * all comparison types and prevents output floods.
     *
     * Will push each difference as 2 Difference objects into the _differences std::vector
     *
     */
    virtual void findDifferences() = 0;

    /**
     * @brief Formats the difference mismatch between two items.
     *
     *  @return a pointer to the Output class, which constructs a formatted stream
     */
    virtual Output *formatDifference() const = 0;

    /**
     * @brief Are two items compared the same. Can only be called after findDifferences.
     *
     * @return true
     * @return false
     */
    bool isSame();

    /**
     * @brief Returns number of differences accounted in findDifferences
     *
     * @return size_t
     */
    size_t diffCount();

protected:
    /**
     * @brief Checks if two files have the same size.
     *
     * @param a Path to file 1
     * @param b Path to file 2
     * @return True if files have the same size, false when they don't
     */
    bool sameFileSize( const fs::path &a, const fs::path &b ) const;

    /**
     * @brief Analyzes a file stream for certain comparison types
     *
     * @param file file stream to be processed
     */
    virtual void parseFile( std::istream &file );

    /**
     * @brief Used for checking if _differences are fully filled up according to the MAX_DIFFERENCES
     * value
     *
     * @return true
     * @return false
     */
    bool notFull();

    std::string _name_1;
    std::string _name_2;
    size_t _diff_count;
    std::vector<Difference *> _differences;
};
