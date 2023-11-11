#pragma once

#include <iostream>
#include <ostream>
#include <vector>

#include "config.h"
#include "difference.h"

/**
 * @brief Used for formatted string stream collection.
 * 
 * 
 */
class Output {
public:
    /**
     * @brief Construct a new Output object and loads it with difference data from Comparator class
     * 
     * @param diffs vector of polymorphic Difference pointers
     */
    Output( const std::vector<Difference *> &diffs, const size_t count );
    virtual ~Output() {
    }
    /**
     * @brief Virtual method for specific manipulation with the already loaded std::stringstream
     * 
     * @param out 
     */
    virtual void run( std::ostringstream &out ) = 0;

protected:
    size_t _diff_count;
    std::stringstream _out;
};


class FileOutput : public Output {
public:
    FileOutput( const std::vector<Difference *> &diffs, const size_t count );
    void run( std::ostringstream &oss ) override;

private:
};


class DirectoryOutput : public Output {
public:
    DirectoryOutput( const std::vector<Difference *> &diffs, const size_t count );
    void run( std::ostringstream &oss ) override;

private:
};