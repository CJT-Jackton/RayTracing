//
// Object.cpp
//
// Created by Jietong Chen on 1/30/2019.
//

#include "Object.h"

int Object::NEXT_ID = 0;

Object::Object() :
        id{ NEXT_ID++ },
        name{ "Object " + id } {
}

Object::Object( std::string name ) :
        id{ NEXT_ID++ },
        name{ std::move( name ) } {
}

int Object::GetID() const {
    return id;
}

std::string Object::ToString() const {
    return name;
}

Object::operator bool() const {
    return true;
}

bool Object::operator==( const Object& other ) const {
    return id == other.id;
}

bool Object::operator!=( const Object& other ) const {
    return id != other.id;
}
