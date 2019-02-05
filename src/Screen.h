//
// Screen.h
//
// Created by Jietong Chen on 2/4/2019.
//

#ifndef SCREEN_H
#define SCREEN_H

class Screen {
public:
    static void SetResolution( int w, int h );

private:
    static int _width;
    static int _height;

public:
    static const int& width = Screen::_width;
    static const int& height = Screen::_height;

}; // Screen

#endif // SCREEN_H
