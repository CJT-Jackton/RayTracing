//
// Screen.h
//
// Access to display information.
//
// Created by Jietong Chen on 2/4/2019.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "pch.h"

namespace RayTracer {
    /**
     * Access to display information.
     */
    class Screen {
    public:
        /**
         * Switches the screen resolution.
         *
         * @param w the width
         * @param h the height
         */
        static void SetResolution( int w, int h );

    private:
        /** width of the screen window in pixels */
        static int _width;

        /** height of the screen window in pixels */
        static int _height;

    public:
        /** width of the screen window in pixels */
        static const int& width;

        /** height of the screen window in pixels */
        static const int& height;

    }; // Screen
} // RayTracer

#endif // SCREEN_H
