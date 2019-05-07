//
// Texture2D.cpp
//
// The implementation of Texture2D.
//
// Created by Jietong Chen on 2/4/2019.
//

#include "pch.h"

using RayTracer::Texture2D;
using RayTracer::BYTE;
using RayTracer::floatBYTE;

/**
 * Create a Texture2D with given size.
 *
 * @param w the width
 * @param h the height
 * @param textureFormat the format of the pixel data in the texture
 */
Texture2D::Texture2D( int w, int h, TextureFormat textureFormat ) :
        Texture{ w, h },
        format{ textureFormat },
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
    if( x < 0 ) {
        x = 0;
    } else if( x >= width ) {
        x = width - 1;
    }

    if( y < 0 ) {
        y = 0;
    } else if( y >= height ) {
        y = height - 1;
    }

    return float4( ( float ) rawData[ 4 * ( y * width + x ) + 0 ] / 255.0f,
                   ( float ) rawData[ 4 * ( y * width + x ) + 1 ] / 255.0f,
                   ( float ) rawData[ 4 * ( y * width + x ) + 2 ] / 255.0f,
                   ( float ) rawData[ 4 * ( y * width + x ) + 3 ] / 255.0f );
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
        color *= 255.0f;

        rawData[ 4 * ( y * width + x ) + 0 ] = ( BYTE ) color.r;
        rawData[ 4 * ( y * width + x ) + 1 ] = ( BYTE ) color.g;
        rawData[ 4 * ( y * width + x ) + 2 ] = ( BYTE ) color.b;
        rawData[ 4 * ( y * width + x ) + 3 ] = ( BYTE ) 255;
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
        color *= 255.0f;

        rawData[ 4 * ( y * width + x ) + 0 ] = ( BYTE ) color.r;
        rawData[ 4 * ( y * width + x ) + 1 ] = ( BYTE ) color.g;
        rawData[ 4 * ( y * width + x ) + 2 ] = ( BYTE ) color.b;
        rawData[ 4 * ( y * width + x ) + 3 ] = ( BYTE ) color.a;
    }
}

/**
 * Fills texture pixels with raw preformatted data.
 *
 * @param data the raw data
 */
void Texture2D::LoadRawTextureData( BYTE* data ) {
    rawData = std::vector< BYTE >{ data, data + ( width * height * 16 ) };
}

/**
 * Read the texture from a png file.
 *
 * @param filename the file name
 */
void Texture2D::ReadTextureFromPNG( const std::string& filename ) {
    png::image< png::basic_rgba_pixel< BYTE > > image( filename );
    png::pixel_buffer< png::basic_rgba_pixel< BYTE >> pixbuf = image.get_pixbuf();

    std::vector< BYTE > buf;

    for( unsigned int i = 0; i < pixbuf.get_height(); ++i ) {
        for( png::basic_rgba_pixel< BYTE > pixel : pixbuf.get_row( i ) ) {
            buf.push_back( pixel.red );
            buf.push_back( pixel.green );
            buf.push_back( pixel.blue );
            buf.push_back( pixel.alpha );
        }
    }

    rawData = buf;
}

/**
 * Save the texture into a png flie.
 *
 * @param filename the file name
 */
void Texture2D::SaveTextureToPNG( const std::string& filename ) const {
    png::image <png::basic_rgba_pixel< BYTE >> image(
            ( unsigned int ) width,
            ( unsigned int ) height );

    if( format == TextureFormat::RGBA32 ) {
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
    } else if( format == TextureFormat::RFloat ) {
        for( int y = 0; y < height; ++y ) {
            for( int x = 0; x < width; ++x ) {
                floatBYTE d{};

                d.byte[ 0 ] = rawData[ ( y * width + x ) * 4 + 0 ];
                d.byte[ 1 ] = rawData[ ( y * width + x ) * 4 + 1 ];
                d.byte[ 2 ] = rawData[ ( y * width + x ) * 4 + 2 ];
                d.byte[ 3 ] = rawData[ ( y * width + x ) * 4 + 3 ];

                float depth = d.f;
                depth *= 256;
                BYTE color = ( BYTE )( depth == 256 ? 255 : depth );

                image[ y ][ x ] = png::basic_rgba_pixel(
                        color, color, color, ( BYTE ) 255 );
            }
        }
    } else if( format == TextureFormat::RGBAFloat ) {
        for( int y = 0; y < height; ++y ) {
            for( int x = 0; x < width; ++x ) {
                floatBYTE d{};

                d.byte[ 0 ] = rawData[ ( y * width + x ) * 16 + 0 ];
                d.byte[ 1 ] = rawData[ ( y * width + x ) * 16 + 1 ];
                d.byte[ 2 ] = rawData[ ( y * width + x ) * 16 + 2 ];
                d.byte[ 3 ] = rawData[ ( y * width + x ) * 16 + 3 ];

                float r = d.f;
                r *= 256;
                BYTE red = ( BYTE )( r >= 256 ? 255 : r );

                d.byte[ 0 ] = rawData[ ( y * width + x ) * 16 + 4 ];
                d.byte[ 1 ] = rawData[ ( y * width + x ) * 16 + 5 ];
                d.byte[ 2 ] = rawData[ ( y * width + x ) * 16 + 6 ];
                d.byte[ 3 ] = rawData[ ( y * width + x ) * 16 + 7 ];

                float g = d.f;
                g *= 256;
                BYTE green = ( BYTE )( g >= 256 ? 255 : g );

                d.byte[ 0 ] = rawData[ ( y * width + x ) * 16 + 8 ];
                d.byte[ 1 ] = rawData[ ( y * width + x ) * 16 + 9 ];
                d.byte[ 2 ] = rawData[ ( y * width + x ) * 16 + 10 ];
                d.byte[ 3 ] = rawData[ ( y * width + x ) * 16 + 11 ];

                float b = d.f;
                b *= 256;
                BYTE blue = ( BYTE )( b >= 256 ? 255 : b );

                d.byte[ 0 ] = rawData[ ( y * width + x ) * 16 + 12 ];
                d.byte[ 1 ] = rawData[ ( y * width + x ) * 16 + 13 ];
                d.byte[ 2 ] = rawData[ ( y * width + x ) * 16 + 14 ];
                d.byte[ 3 ] = rawData[ ( y * width + x ) * 16 + 15 ];

                float a = d.f;
                a *= 256;
                BYTE alpha = ( BYTE )( a >= 256 ? 255 : a );

                image[ y ][ x ] = png::basic_rgba_pixel(
                        red, green, blue, alpha );
            }
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
