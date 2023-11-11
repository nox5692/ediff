#pragma once

#include <fstream>
#include <map>

#include "comparator.h"
#include "cssStyle.h"
#include "output.h"

class cssComparator : public Comparator {
public:
    cssComparator( const std::string &file_1, const std::string &file_2 )
        : Comparator( file_1, file_2 ), _file_1( _name_1 ), _file_2( _name_2 ) {
        if ( !_file_1.is_open() )
            throw std::logic_error( "Error: " + _name_1 + " could not be opened." );
        if ( !_file_2.is_open() )
            throw std::logic_error( "Error: " + _name_2 + " could not be opened." );
    }
    ~cssComparator();

    /**
     * @brief Compares computed styles of 2 CSS files
     * 
     * Utilizes the laodStyles() method for individual file and only works with std::map while using defined operators from the Selector class. 
     * 
     */
    void findDifferences() override;
    Output *formatDifference() const override;

private:
/**
     * @brief Collects information about all Selectors in a file 
     *
     */
    void loadStyles( std::istream &file, std::map<std::string, Selector> &computed );

    std::ifstream _file_1;
    std::ifstream _file_2;
    std::map<std::string, Selector> _computed_1;
    std::map<std::string, Selector> _computed_2;
};
