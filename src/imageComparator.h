#pragma once

#include <fstream>
#include <cstdio>

#include "comparator.h"
#include "color.h"
#include "output.h"

#include <png.h>

class imageComparator : public Comparator {
public:
    imageComparator( const std::string &file_1, const std::string &file_2 )
        : Comparator( file_1, file_2 ) {
            _file_1 = fopen( file_1.c_str(), "rb" );
            _file_2 = fopen( file_2.c_str(), "rb" );
            if ( !_file_1 or !_file_2 )
                throw std::logic_error("Faulty PNG file.");

    }
    ~imageComparator();

    /**
     * @brief Utilizes the getPixelCOlors() method.
     * 
     * Then only works with individual histograms constructed and overloaded operators of the Color class.
     * 
     */
    void findDifferences() override;
    Output *formatDifference() const override;

private:
    /**
     * @brief Utilizes the libPNG C style library and performs a PNG file analysis according to the library specification.
     *  
     * @return std::vector<Color> Unique colors with their individual pixel count.
     */
    std::vector<Color> getPixelColors( FILE * file );

    FILE * _file_1;
    FILE * _file_2;
    std::vector<Color> _file_data_1;
    std::vector<Color> _file_data_2;
};
