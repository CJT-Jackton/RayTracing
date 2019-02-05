//
// Sphere.cpp
//
// Created by Jietong Chen on 1/31/2019.
//

#include "Sphere.h"

Sphere::Sphere() :
        center{},
        radius{ 1 } {
}

Sphere::Sphere( const Sphere& other ) :
        Primitive( other ),
        center{ other.center },
        radius{ other.radius } {
}

Sphere* Sphere::Clone() const {
    return new Sphere( *this );
}

float Sphere::Intersect( Ray ray ) const {
    float B = 2.0f * ( ( ray.direction.x * ( ray.origin.x - center.x ) +
                         ray.direction.y * ( ray.origin.y - center.y ) +
                         ray.direction.z * ( ray.origin.z - center.z ) ) );
    float C = pow( ray.origin.x - center.x, 2 ) +
              pow( ray.origin.y - center.y, 2 ) +
              pow( ray.origin.z - center.z, 2 ) -
              pow( radius, 2 );

    float delta = pow( B, 2 ) - 4 * C;

    if( delta < 0 ) {
        return -1;
    } else if( delta == 0 ) {
        return -B / 2.0f;
    } else {
        if( ( -B - delta ) / 2.0f > 0 ) {
            return ( -B - delta ) / 2.0f;
        } else {
            return ( -B + delta ) / 2.0f;
        }
    }
}

Sphere* Sphere::ToWorldSpace( float4x4 localToWorldMatrix ) const {
    Sphere* sphere = new Sphere( *this );

    /*float4 tmp = mul( float4( center.x, center.y, center.z, .0f ),
                      localToWorldMatrix );*/
    sphere->center = mul( float4( center.x, center.y, center.z, 0.0f ),
                          localToWorldMatrix ).xyz;

    return sphere;
}

Sphere* Sphere::ToCameraSpace( float4x4 worldToCameraMatrix ) const {
    Sphere* sphere = new Sphere( *this );

    //float4 tmp = mul( float4( center.x, center.y, center.z, .0f ),
    //                  worldToCameraMatrix );
    sphere->center = mul( float4( center.x, center.y, center.z, 0.0f ),
                          worldToCameraMatrix ).xyz;

    return sphere;
}
