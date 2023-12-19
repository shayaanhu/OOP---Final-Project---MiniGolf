#include "vector2f.hpp"

// Implementation of member functions
Vector2f::Vector2f() : x(0.0f), y(0.0f) {}

Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

Vector2f::Vector2f(const Vector2f& other) : x(other.x), y(other.y) {}

// OPERATOR OVERLOADING
Vector2f& Vector2f::operator=(const Vector2f& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Vector2f Vector2f::operator+(const Vector2f& other) const {
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f& other) const {
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator*(float scalar) const {
    return Vector2f(x * scalar, y * scalar);
}

float Vector2f::dot(const Vector2f& other) const {
    return x * other.x + y * other.y;
}

float Vector2f::magnitude() const {
    return std::sqrt(x * x + y * y);
}

// Greater than operator
bool Vector2f::operator>(const Vector2f& other) const {
    return magnitude() > other.magnitude();
}

// Lesser than operator
bool Vector2f::operator<(const Vector2f& other) const {
    return magnitude() < other.magnitude();
}

Vector2f Vector2f::normalize() const {
    float mag = magnitude();
    if (mag != 0.0f) {
        return Vector2f(x / mag, y / mag);
    }
    return *this; // Avoid division by zero
}

void Vector2f::display() const {
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}
