//
// Texture2D.h
//
// Class for texture handling.
//
// Created by Jietong Chen on 2/4/2019.
//

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "Texture.h"

namespace RayTracing {
    /**
     * Class for texture handling.
     */
    class Texture2D : public Texture {
    public:
        /**
         * Create a Texture2D with given size.
         *
         * @param w the width
         * @param h the height
         */
        Texture2D( int w, int h );

        /**
         * Get the pixel value at given position.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         *
         * @return the pixel value
         */
        float4 GetPixel( int x, int y ) const;

        /**
         * Set the pixel value at given position.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         * @param color the color
         */
        void SetPixel( int x, int y, float3 color );

        /**
         * Set the pixel value at given position.
         *
         * @param x the x coordinate
         * @param y the y coordinate
         * @param color the color
         */
        void SetPixel( int x, int y, float4 color );

        /**
         * Fills texture pixels with raw preformatted data.
         *
         * @param data the raw data
         */
        void LoadRawTextureData( BYTE* data );

        /**
         * Save the texture into a png flie.
         *
         * @param filename the file name
         */
        void SaveTextureToPNG( std::string filename ) const;

        /**
         * Get the pointer to the texture native data.
         *
         * @return the pointer to the texture native data
         */
        BYTE* GetNativeTexturePtr() const override;

    private:
        /** the texture data */
        std::vector< BYTE > rawData;

    }; // Texture2D
} // RayTracing

#endif // TEXTURE2D_H