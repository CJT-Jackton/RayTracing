//
// GameObject.cpp
//
// Created by Jietong Chen on 1/30/2019.
//

#include "GameObject.h"

GameObject::GameObject() :
        Object{},
        transform{} {
}

GameObject::GameObject( std::string name ) :
        Object{ std::move( name ) },
        transform{} {
}

void GameObject::SetActive( bool value ) {
    active = value;
}

void GameObject::MoveToScene( Scene& s ) {
    scene = &s;
}
