//
// Object.cpp
//
// The implementation of Object.
//
// Created by Jietong Chen on 1/30/2019.
//

#include "pch.h"

using RayTracing::Object;

int Object::NEXT_ID = 0;

/**
 * Create an Object.
 */
Object::Object() :
        id{ NEXT_ID++ },
        name{ "Object " + id } {
}

/**
 * Create an Object with name.
 *
 * @param name the name
 */
Object::Object( std::string name ) :
        id{ NEXT_ID++ },
        name{ std::move( name ) } {
}

/**
 * Copy from another Object.
 *
 * @param other the Object to copy from
 */
Object::Object( const Object& other ) :
        id{ NEXT_ID++ },
        name{ other.name + " Copy" } {
}

/**
 * Assign the Object with an other Object.
 *
 * @param other the Object to assign
 *
 * @return this Object
 */
Object& Object::operator=( const Object& other ) {
    if( this != &other ) {
        name = other.name;
    }

    return *this;
}

/**
 * Get the id of the Object.
 *
 * @return the id of the Object
 */
int Object::GetID() const {
    return id;
}

/**
 * Convert the Object into string format.
 *
 * @return the string representation of the Object
 */
std::string Object::ToString() const {
    return name;
}

/**
 * Determine whether the Object exist or not.
 *
 * @return true if the Object exist
 */
Object::operator bool() const {
    return true;
}

/**
 * Compare with another Object. Return true if two Objects are indentical,
 * false if not.
 *
 * @param other the Object to compare with
 *
 * @return true if two Objects are the same Object, false if not
 */
bool Object::operator==( const Object& other ) const {
    return id == other.id;
}

/**
 * Compare with another Object. Return true if two Objects are different,
 * false if not.
 *
 * @param other the Object to compare with
 *
 * @return true if two Objects are different Objects, false if not
 */
bool Object::operator!=( const Object& other ) const {
    return id != other.id;
}
