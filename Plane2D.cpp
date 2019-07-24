#include "Plane2D.h"

// @DefaultConstructor
Plane2D::Plane2D() : start_({0, 0}), end_({0, 0}) {}

// @CopyConstructor
Plane2D::Plane2D(const Plane2D &plane)
{
    this->start_ = plane.start();
    this->end_ = plane.end();
}

Plane2D::Plane2D(const float x1, const float y1, const float x2, const float y2)
{
    this->start_ = Vector2D(x1, y1);
    this->end_ = Vector2D(x2, y2);
}

Plane2D::Plane2D(const Vector2D& start, const Vector2D& end)
{
    this->start_ = Vector2D(start);
    this->end_ = Vector2D(end);
}

Plane2D::Plane2D(const Vector2D& start, const float angle, const float length)
{
    this->start_ = Vector2D(start);
    this->end_ = Vector2D::fromPolar(angle, length) + this->start_;
}

float Plane2D::angle() const
{
    // Return the angle of the sum of the vectors describing the plane
    Vector2D sum = this->start_ + this->end_;
    return sum.direction();
}

float Plane2D::length() const
{
    // Return the length of the sum of the vectors describing the plane
    Vector2D sum = this->start_ + this->end_;
    return sum.magnitude();
}

Vector2D Plane2D::start() const 
{
    return this->start_;
}

Vector2D Plane2D::end() const
{
    return this->end_;
}
