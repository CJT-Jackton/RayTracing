//
// Object.h
//
// The base class of all object.
//
// Created by Jietong Chen on 1/30/2019.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "pch.h"

using namespace hlslpp;

namespace RayTracer {
    /**
     * The base class of all object.
     */
    class Object {
    public:
        /**
         * Create an Object.
         */
        Object();

        /**
         * Create an Object with name.
         *
         * @param name the name
         */
        Object( std::string name );

        /**
         * Copy from another Object.
         *
         * @param other the Object to copy from
         */
        Object( const Object& other );

        /**
         * Assign the Object with an other Object.
         *
         * @param other the Object to assign
         *
         * @return this Object
         */
        Object& operator=( const Object& other );

        /**
         * Object deconstructor is default.
         */
        virtual ~Object() = default;

        /**
         * Get the id of the object.
         *
         * @return the id of the Object
         */
        int GetID() const;

        /**
         * Convert the Object into string format.
         *
         * @return the string representation of the Object
         */
        std::string ToString() const;

        /**
         * Determine whether the Object exist or not.
         *
         * @return true if the object exist
         */
        virtual operator bool() const;

        /**
         * Compare with another Object. Return true if two Objects are
         * indentical, false if not.
         *
         * @param other the Object to compare with
         *
         * @return true if two Objects are the same Object, false if not
         */
        bool operator==( const Object& other ) const;

        /**
         * Compare with another Object. Return true if two Objects are
         * different, false if not.
         *
         * @param other the Object to compare with
         *
         * @return true if two Objects are different Objects, false if not
        */
        bool operator!=( const Object& other ) const;

    protected:
        /** the name of the Object */
        std::string name;

        /** the id of the Object */
        const int id;

    private:
        /** id of next created Object */
        static int NEXT_ID;

    }; // Object
} // RayTracer

#endif // OBJECT_H
