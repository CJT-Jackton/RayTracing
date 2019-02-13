//
// Mesh.cpp
//
// The implementation of Mesh.
//
// Created by Jietong Chen on 2/1/2019.
//

#include "pch.h"

using RayTracing::Mesh;
using RayTracing::Object;
using RayTracing::Primitive;

/**
 * Create a empty Mesh.
 */
Mesh::Mesh() :
        Object{ "Empty-Mesh" } {
}

/**
 * Add a primitive to the mesh.
 *
 * @param primitive the primitive
 */
void Mesh::AddPrimitive( std::unique_ptr< Primitive > primitive ) {
    primitive->mesh = this;
    primitives.emplace_back( std::move( primitive ) );
}

/**
 * Get the array of primitive.
 *
 * @return the array of primitive
 */
const std::vector< std::unique_ptr< Primitive > >& Mesh::GetPrimitives() const {
    return primitives;
}

bool Mesh::ReadOBJ( const std::string& filename ) {
    try {
        std::ifstream is( filename );
        std::string line;
        std::string ch;

        std::vector< float3 > vertices;
        std::vector< float3 > normals;
        std::vector< float2 > uvs;

        float x, y, z;

        if( !is.good() ) {
            throw std::runtime_error( "" );
        }

        while( is >> ch ) {
            if( ch == "v" ) {
                is >> x >> y >> z;
                vertices.emplace_back( float3( x, y, z ) );
            } else if( ch == "vt" ) {
                is >> x >> y;
                uvs.emplace_back( float2( x, y ) );
            } else if( ch == "vn" ) {
                is >> x >> y >> z;
                normals.emplace_back( normalize( float3( x, y, z ) ) );
            } else if( ch == "f" ) {
                std::unique_ptr< Triangle > triangle = std::make_unique< Triangle >();

                std::getline( is, line );
                std::istringstream iss( line );

                std::vector< std::string >
                f( std::istream_iterator< std::string > { iss },
                std::istream_iterator< std::string >());

                if( f[ 0 ].find( '/' ) == std::string::npos ) {
                    triangle->vertices[ 0 ] =
                            vertices[ std::stoi( f[ 0 ] ) - 1 ];
                    triangle->vertices[ 1 ] =
                            vertices[ std::stoi( f[ 1 ] ) - 1 ];
                    triangle->vertices[ 2 ] =
                            vertices[ std::stoi( f[ 2 ] ) - 1 ];
                } else {
                    int pos0 = f[ 0 ].find( '/' );
                    int pos1 = f[ 1 ].find( '/' );
                    int pos2 = f[ 2 ].find( '/' );

                    triangle->vertices[ 0 ] = vertices[ std::stoi(
                            f[ 0 ].substr( 0, pos0 ) ) - 1 ];
                    triangle->vertices[ 1 ] = vertices[ std::stoi(
                            f[ 1 ].substr( 0, pos1 ) ) - 1 ];
                    triangle->vertices[ 2 ] = vertices[ std::stoi(
                            f[ 2 ].substr( 0, pos2 ) ) - 1 ];

                    if( f[ 0 ][ pos0 + 1 ] != '/' ) {
                        f[ 0 ].erase( 0, pos0 + 1 );
                        f[ 1 ].erase( 0, pos1 + 1 );
                        f[ 2 ].erase( 0, pos2 + 1 );

                        pos0 = f[ 0 ].find( '/' );
                        pos1 = f[ 1 ].find( '/' );
                        pos2 = f[ 2 ].find( '/' );

                        triangle->uv[ 0 ] = uvs[ std::stoi(
                                f[ 0 ].substr( 0, pos0 ) ) - 1 ];
                        triangle->uv[ 1 ] = uvs[ std::stoi(
                                f[ 1 ].substr( 0, pos1 ) ) - 1 ];
                        triangle->uv[ 2 ] = uvs[ std::stoi(
                                f[ 2 ].substr( 0, pos2 ) ) - 1 ];

                        f[ 0 ].erase( 0, pos0 + 1 );
                        f[ 1 ].erase( 0, pos1 + 1 );
                        f[ 2 ].erase( 0, pos2 + 1 );
                    } else {
                        f[ 0 ].erase( 0, pos0 + 2 );
                        f[ 1 ].erase( 0, pos1 + 2 );
                        f[ 2 ].erase( 0, pos2 + 2 );
                    }

                    triangle->normals[ 0 ] = normals[ std::stoi( f[ 0 ] ) - 1 ];
                    triangle->normals[ 1 ] = normals[ std::stoi( f[ 1 ] ) - 1 ];
                    triangle->normals[ 2 ] = normals[ std::stoi( f[ 2 ] ) - 1 ];
                }

                AddPrimitive( std::move( triangle ) );

            } else if( ch == "vp" ) {
                std::cerr << "Parameter space vertices is not supported"
                          << std::endl;
                is.ignore( std::numeric_limits< std::streamsize >::max(),
                           '\n' );
            } else {
                is.ignore( std::numeric_limits< std::streamsize >::max(),
                           '\n' );
            }
        }

        is.close();
    }
    catch( std::runtime_error error ) {
        std::cerr << error.what() << std::endl;
        return false;
    }

    return true;
}
