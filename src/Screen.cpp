//
// Screen.cpp
//
// Created by Jietong Chen on 2/4/2019.
//

#include "Screen.h"

void Screen::SetResolution( int w, int h ) {
    if( w > 0 && h > 0 ) {
        Screen::_width = w;
        Screen::_height = h;
    }
}
