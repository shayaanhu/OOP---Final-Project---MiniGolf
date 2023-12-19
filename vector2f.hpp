#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <iostream>
#include <cmath>

class Vector2f {
public:
    float x, y;

    // Constructors
    Vector2f();
    Vector2f(float x, float y);

    // Copy constructor
    Vector2f(const Vector2f& other);

    // OPERATOR OVERLOADING:
    // Assignment operator
    Vector2f& operator=(const Vector2f& other);

    // Addition of vectors
    Vector2f operator+(const Vector2f& other) const;

    // Subtraction of vectors
    Vector2f operator-(const Vector2f& other) const;

    // Scalar multiplication
    Vector2f operator*(float scalar) const;

    // Greater than operator
    bool operator>(const Vector2f& left, const Vector2f& right);

    // Lesser than operator
    bool operator<(const Vector2f& left, const Vector2f& right);

    // Dot product of vectors
    float dot(const Vector2f& other) const;

    // Magnitude (length) of the vector
    float magnitude() const;

    // Normalize the vector (make it a unit vector)
    Vector2f normalize() const;

    // Display the vector
    void display() const;
};

#endif // VECTOR2F_HPP

