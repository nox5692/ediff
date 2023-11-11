#include <algorithm>
#include <exception>

#include "imageComparator.h"

imageComparator::~imageComparator() {
    if ( _file_1 != nullptr )
        fclose( _file_1 );
    if ( _file_2 != nullptr )
        fclose( _file_2 );
}

std::vector<Color> imageComparator::getPixelColors( FILE *file ) {
    std::vector<Color> pixel_colors; // unique colors with their respective pixel count in the image

    if ( !file ) {
        throw std::runtime_error( "PNG Error." );
        fclose( file );
        return pixel_colors;
    }

    png_structp pngPtr = png_create_read_struct( PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr );
    if ( !pngPtr ) {
        throw std::runtime_error( "PNG Error." );
        png_destroy_read_struct( &pngPtr, nullptr, nullptr );
        fclose( file );
        return pixel_colors;
    }

    png_infop infoPtr = png_create_info_struct( pngPtr );
    if ( !infoPtr ) {
        throw std::runtime_error( "PNG Error." );
        png_destroy_read_struct( &pngPtr, nullptr, nullptr );
        fclose( file );
        return pixel_colors;
    }

    if ( setjmp( png_jmpbuf( pngPtr ) ) ) {
        throw std::runtime_error( "PNG Error." );
        png_destroy_read_struct( &pngPtr, &infoPtr, nullptr );
        fclose( file );
        return pixel_colors;
    }

    png_init_io( pngPtr, file );
    png_read_info( pngPtr, infoPtr );

    png_uint_32 width, height;
    int bitDepth, colorType, interlaceMethod;
    png_get_IHDR( pngPtr, infoPtr, &width, &height, &bitDepth, &colorType, &interlaceMethod,
                  nullptr, nullptr );

    // Allocate memory for the pixel data
    png_bytep *rowPointers = new png_bytep[height];
    for ( png_uint_32 y = 0; y < height; ++y )
        rowPointers[y] = new png_byte[png_get_rowbytes( pngPtr, infoPtr )];

    // Read the image data
    png_read_image( pngPtr, rowPointers );

    // Access the pixel data and perform color analysis
    for ( png_uint_32 y = 0; y < height; ++y ) {
        for ( png_uint_32 x = 0; x < width; ++x ) {
            png_bytep pixel = &( rowPointers[y][x * 4] ); // Each pixel is 4 bytes (RGBA)
            Color color;
            color._red = pixel[0];
            color._green = pixel[1];
            color._blue = pixel[2];
            color._alpha = pixel[3];
            color._count = 1;

            auto color_it = std::find( pixel_colors.begin(), pixel_colors.end(), color );
            if ( color_it == pixel_colors.end() )
                pixel_colors.push_back( color );
            else
                color_it->_count++;
        }
    }


    for ( png_uint_32 y = 0; y < height; ++y )
        delete[] rowPointers[y];
    delete[] rowPointers;

    png_destroy_read_struct( &pngPtr, &infoPtr, nullptr );

    return pixel_colors;
}

void imageComparator::findDifferences() {
    _file_data_1 = getPixelColors( _file_1 );
    _file_data_2 = getPixelColors( _file_2 );

    for ( const Color &color : _file_data_1 ) {
        auto it = std::find( _file_data_2.begin(), _file_data_2.end(), color );
        if ( it == _file_data_2.end() ) {
            Color new_color( color._red, color._green, color._blue, color._alpha );
            new_color._count = 0;
            _file_data_2.push_back( new_color );
        }
    }

    for ( const Color &color : _file_data_2 ) {
        auto it = std::find( _file_data_1.begin(), _file_data_1.end(), color );
        if ( it == _file_data_1.end() ) {
            Color new_color( color._red, color._green, color._blue, color._alpha );
            new_color._count = 0;
            _file_data_1.push_back( new_color );
        }
    }

    for ( const Color &color : _file_data_1 ) {
        auto it = std::find( _file_data_2.begin(), _file_data_2.end(), color );
        if ( *it == color && ( it->_count != color._count ) ) {
            if ( notFull() ) {
                _diff_count++;
                _differences.push_back( new ImageDifference( color, *it ) );
            }
        }
    }
}

Output *imageComparator::formatDifference() const {
    return new FileOutput( _differences, _diff_count );
}