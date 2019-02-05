//
// Object.h
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef OBJECT_H
#define OBJECT_H

#include <hlsl++.h>
#include <string>

using namespace hlslpp;

/**
 * The base class of all object.
 */
class Object {
public:
    /**
     * Create an object.
     */
    Object();

    Object( std::string name );

    /**
     * Object deconstructor is default.
     */
    virtual ~Object() = default;

    /**
     * Get the id of the object.
     *
     * @return the id of the object
     */
    int GetID() const;

    std::string ToString() const;

    /**
     * Determine whether the object exist or not.
     *
     * @return true if the object exist
     */
    operator bool() const;

    /**
     * Compare two objects. Return true if two objects are indentical, false
     * if not.
     *
     * @param a the firts object
     * @param b the second object
     *
     * @return true if two objects are the same, false if not
     */
    bool operator==( const Object& other ) const;

    /**
     * Compare two objects. Return true if two objects are different, false
     * if not.
     *
     * @param a the first object
     * @param b the second object
     *
     * @return true if two objects are different, false if not
     */
    bool operator!=( const Object& other ) const;

protected:
    /** the name of the object */
    std::string name;

    /** the id of the object */
    const int id;

private:
    /** id */
    static int NEXT_ID;

}; // Object

#endif // OBJECT_H
