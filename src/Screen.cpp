//
// Screen.cpp
//
// The implementation of Screen.
//
// Created by Jietong Chen on 2/4/2019.
//

#include "pch.h"

using RayTracer::Screen;

int Screen::_width = DEFAULT_SCREEN_WIDTH;
int Screen::_height = DEFAULT_SCREEN_HEIGHT;

const int& Screen::width = Screen::_width;
const int& Screen::height = Screen::_height;

/**
 * Switches the screen resolution.
 *
 * @param w the width
 * @param h the height
 */
void Screen::SetResolution( int w, int h ) {
    if( w > 0 && h > 0 ) {
        Screen::_width = w;
        Screen::_height = h;
    }
}
