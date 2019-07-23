#include "Plane2D.h"

// @DefaultConstructor
Plane2D::Plane2D() : start_({0, 0}), end_({0, 0}) {}

// @CopyConstructor
Plane2D::Plane2D(const Plane2D &plane)
{
    this->start_ = plane.start();
    this->end_ = plane.end();
}

Plane2D::Plane2D(const Vector2D& start, const Vector2D& end)
{
    this->start_ = start;
    this->end_ = end;
}

float Plane2D::angle() const
{
    // Return the angle of the sum of the vectors describing the plane
    Vector2D sum = this->start_ + this->end_;
    return sum.heading();
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
