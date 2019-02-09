//
// Texture2D.cpp
//
// The implementation of Texture2D.
//
// Created by Jietong Chen on 2/4/2019.
//

#include "pch.h"

using RayTracing::Texture2D;
using RayTracing::BYTE;

/**
 * Create a Texture2D with given size.
 *
 * @param w the width
 * @param h the height
 */
Texture2D::Texture2D( int w, int h ) :
        Texture{ w, h },
        rawData( w * h * 4, 0 ) {
}

/**
 * Get the pixel value at given position.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 *
 * @return the pixel value
 */
float4 Texture2D::GetPixel( int x, int y ) const {
    if( x < 0 || x >= width || y < 0 || y >= height ) {
        return float4( 0, 0, 0, 0 );
    } else {
        return float4( ( float ) rawData[ 4 * ( x * width + y ) + 0 ] / 255.0f,
                       ( float ) rawData[ 4 * ( x * width + y ) + 1 ] / 255.0f,
                       ( float ) rawData[ 4 * ( x * width + y ) + 2 ] / 255.0f,
                       ( float ) rawData[ 4 * ( x * width + y ) + 3 ] /
                       255.0f );
    }
}

/**
 * Set the pixel value at given position.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param color the color
 */
void Texture2D::SetPixel( int x, int y, float3 color ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        rawData[ 4 * ( x * width + y ) + 0 ] = ( BYTE ) ( color.r * 255 );
        rawData[ 4 * ( x * width + y ) + 1 ] = ( BYTE ) ( color.g * 255 );
        rawData[ 4 * ( x * width + y ) + 2 ] = ( BYTE ) ( color.b * 255 );
        rawData[ 4 * ( x * width + y ) + 3 ] = ( BYTE ) ( 1.0f * 255 );
    }
}

/**
 * Set the pixel value at given position.
 *
 * @param x the x coordinate
 * @param y the y coordinate
 * @param color the color
 */
void Texture2D::SetPixel( int x, int y, float4 color ) {
    if( x >= 0 && x < width && y >= 0 && y < height ) {
        rawData[ 4 * ( x * width + y ) + 0 ] = ( BYTE ) ( color.r * 255 );
        rawData[ 4 * ( x * width + y ) + 1 ] = ( BYTE ) ( color.g * 255 );
        rawData[ 4 * ( x * width + y ) + 2 ] = ( BYTE ) ( color.b * 255 );
        rawData[ 4 * ( x * width + y ) + 3 ] = ( BYTE ) ( color.a * 255 );
    }
}

/**
 * Fills texture pixels with raw preformatted data.
 *
 * @param data the raw data
 */
void Texture2D::LoadRawTextureData( BYTE* data ) {
    rawData = std::vector< BYTE >{ data, data + ( width * height * 4 ) };
}

/**
 * Save the texture into a png flie.
 *
 * @param filename the file name
 */
void Texture2D::SaveTextureToPNG( std::string filename ) const {
//    try {
//        FILE* fp = fopen( filename.c_str(), "wb" );
//
//        if( !fp ) {
//            throw std::runtime_error( "Cannot open file " + filename + "!" );
//        }
//
//        png_structp png = png_create_write_struct( PNG_LIBPNG_VER_STRING, NULL,
//                                                   NULL, NULL );
//
//        if( !png ) {
//            throw std::runtime_error( "Cannot create png file!" );
//        }
//
//        png_infop info = png_create_info_struct( png );
//
//        if( !info ) {
//            throw std::runtime_error( "Cannot create png info!" );
//        }
//
//        if( setjmp( png_jmpbuf( png ) ) ) {
//            throw std::runtime_error( "Cannot set up longjmp!" );
//        }
//
//        png_byte** row_pointers = new png_byte* [height];
//
//        for( int y = 0; y < height; ++y ) {
//            row_pointers[ y ] = new png_byte[width];
//
//            for( int x = 0; x < width * 4; ++x ) {
//                row_pointers[ y ][ x ] = rawData[ y * width * 4 + x ];
//            }
//        }
//
//        png_init_io( png, fp );
//
//        png_set_IHDR(
//                png,
//                info,
//                ( png_uint_32 ) width, ( png_uint_32 ) height,
//                8,
//                PNG_COLOR_TYPE_RGBA,
//                PNG_INTERLACE_NONE,
//                PNG_COMPRESSION_TYPE_DEFAULT,
//                PNG_FILTER_TYPE_DEFAULT
//        );
//
//        png_write_info( png, info );
//        png_write_image( png, row_pointers );
//        png_write_end( png, NULL );
//
//        for( int y = 0; y < height; ++y ) {
//            free( row_pointers[ y ] );
//        }
//
//        free( row_pointers );
//
//        fclose( fp );
//    } catch( std::runtime_error const& error ) {
//        std::cerr << "Error: " << error.what() << std::endl;
//    }

    png::image< png::basic_rgba_pixel< BYTE > > image( ( unsigned int ) width,
                                                       ( unsigned int ) height );

    for( int y = 0; y < height; ++y ) {
        for( int x = 0; x < width; ++x ) {
            image[ y ][ x ] = png::basic_rgba_pixel(
                    rawData[ ( y * width + x ) * 4 + 0 ],
                    rawData[ ( y * width + x ) * 4 + 1 ],
                    rawData[ ( y * width + x ) * 4 + 2 ],
                    rawData[ ( y * width + x ) * 4 + 3 ]
            );
        }
    }

    image.write( filename );
}

/**
 * Get the pointer to the texture native data.
 *
 * @return the pointer to the texture native data
 */
BYTE* Texture2D::GetNativeTexturePtr() const {
    return const_cast<BYTE*>(rawData.data());
}
