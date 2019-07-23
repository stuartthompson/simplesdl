#include <math.h>
#include "Vector2D.h"

// @DefaultConstructor
Vector2D::Vector2D() : x(0), y(0) {}

// @CopyConstructor
Vector2D::Vector2D(const Vector2D &vector)
{
    this->x = vector.x;
    this->y = vector.y;
}

// @Constructor
Vector2D::Vector2D(const Point2D& point) {
    this->x = point.x;
    this->y = point.y;
}

// @Constructor
Vector2D::Vector2D(const float heading, const float magnitude)
{
    // Since we know hypotenuse (magnitude) and angle, we can use soh and cah from sohcahtoa
    //  (x): cos(a) = a/h  ==>  a = cos(a)*h
    //  (y): sin(a) = o/h  ==>  o = sin(a)*h

    this->x = cos(heading) * magnitude; // x (width)
    this->y = sin(heading) * magnitude; // y (height)
}

// Assignment operators

Vector2D& Vector2D::operator=(const Vector2D& vector) {
    this->x = vector.x;
    this->y = vector.y;
    return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vector) {
    this->x -= vector.x;
    this->y -= vector.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vector) {
    this->x *= vector.x;
    this->y *= vector.y;
    return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vector) {
    this->x /= vector.x;
    this->y /= vector.y;
    return *this;
}

// Arithmetic operators

Vector2D Vector2D::operator+(const Vector2D& vector) const {
    return Vector2D(this->x + vector.x, this->y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D& vector) const {
    return Vector2D(this->x - vector.x, this->y - vector.y);
}

Vector2D Vector2D::operator*(const Vector2D& vector) const {
    return Vector2D(this->x * vector.x, this->y * vector.y);
}

Vector2D Vector2D::operator/(const Vector2D& vector) const {
    return Vector2D(this->x / vector.x, this->y / vector.y);
}

// Query functions

float Vector2D::heading() const
{
    // sohcahtoa - so tan(a) = o/a  ==>  atan(y/x);
    return atan(this->y / this->x);
}

float Vector2D::magnitude() const
{
    // Pythagorean theorem (a^2 + b^2 = c^2), therefore c = sqrt(a*a + b*b)
    return sqrt(this->x * this->x + this->y * this->y);
}

float Vector2D::distanceFrom(const Vector2D& vector) const {
    // Calculate the length of the difference of the vectors
    Vector2D diff = *this - vector;
    return diff.magnitude();
}
