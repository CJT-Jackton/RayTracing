# Ray Tracing

Offline rendering application by ray tracing.

### Features

- Spatial data structure (k-d tree)
- Photon mapping
- Procedural texture

## Requirements

C++14 or higher. Tested on MSVC v141, no tested on other comilper yet. 

- [hlsl++](https://github.com/redorav/hlslpp)    Vector, Matrix library provided a HLSL like syntax.
- [libpng](http://www.libpng.org/pub/png/libpng.html)    Library to handle .PNG file.
- [png++](https://www.nongnu.org/pngpp/)   C++ wrapper for libpng library.

## Screenshots (work in progress)

![screenshot](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Reflection_1.png "Screenshot 1")
    *Reflection*

![screenshot](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Refraction_2.png "Screenshot 2")
    *Refraction & Translucent shadow*

## Shading

### Phong shading model

![phong](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Checkpoint3_Phong.png "Phong Shading")

### Blinn-Phong shading model

![blinn-phong](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Checkpoint3_Blinn-Phong.png "Blinn-Phong Shading")

## Texture

![Texture](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Texture_Bilinear.png "Texture mapping")

### Procedural Texture

A procedural texture compute the color while sampling instead of using stored data. 

#### Checkerboard 2D

The checkerboard 2D procedural texture is pretty straightforward. If the sample point fall within the bottom-left or upper-right region it return the main color, otherwise it return the secondary color.

![Checkerboard 2D](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Procedural_Texture_Checkerboard2D.png "Procedural Texture Checkerboard2D")
    *Checkerboard 2D texture on the plane*

#### Perlin noise

Perlin noise is a type of gradient noise developed by Ken Perlin in 1983[[1](https://dl.acm.org/citation.cfm?doid=325165.325247)]. This program use a improved version of Perlin noise[[2](https://mrl.nyu.edu/~perlin/paper445.pdf)]. The Java implementation written by Ken Perlin himself can be found [here](https://cs.nyu.edu/~perlin/noise/).

![Perlin noise](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Procedural_Texture_Perlin_Noise.png "Procedural Texture Perlin Noise")
    *Perlin noise on the plane*

## Anti-aliasing

Multisample anti-aliasing with 4 rays per pixel.
After tried out multiple sampling pattern, I found 4-Rooks pattern (Rotated grid supersampling) produced the best result in visual.

![NoAA](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Checkpoint3_NoAA.png "No Anti-aliasing")

No anti-aliasing.

![MSAA4x](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Checkpoint3_MSAA4x.png "Multisample Anti-aliasing")

With MSAA4x anti-aliasing.

![NoAA vs MSAA4x](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/Checkpoint3_NoAAvsMSAA4x.png "NoAA vs MSAA4x")

Side by side comparison.

## Tone mapping

There are multiple ways to convert the HDR image into LDR space. However the ACES film tone mapping is the most widely accepted and used tone mapping algorithm.

### Tone mapping

#### None
![None](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/ToneMapping_None.png "No tone mapping")

#### Reinhard
![Reinhard](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/ToneMapping_Reinhard.png "Reinhard tone mapping")

#### Ward's
![Ward](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/ToneMapping_Ward.png "Ward's tone mapping")

#### ACES Filmic
![ACES](https://raw.githubusercontent.com/CJT-Jackton/RayTracing/master/Screenshots/ToneMapping_ACES.png "ACES filmic tone mapping")

## Author
Jietong Chen
