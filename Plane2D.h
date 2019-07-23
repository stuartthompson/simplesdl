#pragma once

#include "Vector2D.h"

/**
 * Represents a plane in 2-dimensional space.
 * This is essentially a line.
 */
class Plane2D
{
public:
    /**
     * Initializes a 2D plane of zero length at the origin.
     */
    Plane2D();

    /**
     * Initializes a 2D plane from another plane.
     * 
     * @param plane The plane to initialize from.
     */
    Plane2D(const Plane2D& plane);

    /**
     * Initializes a 2D plane from a pair of 2D coordinates.
     */
    Plane2D(float x1, float y1, float x2, float y2);

    /**
     * Initializes a 2D plane from a pair of 2D vectors.
     * 
     * @param start The vector describing the start of the new plane.
     * @param end The vector describing the end of the new plane.
     */
    Plane2D(const Vector2D& start, const Vector2D& end);

    /**
     * Returns the angle of the vector this plane describes.
     */
    float angle() const;

    /**
     * Returns the length of this plane.
     */
    float length() const;

    /**
     * Returns the vector describing the start of this plane.
     */
    Vector2D start() const;

    /**
     * Returns the vector describing the end of this plane.
     */
    Vector2D end() const;

private:
    Vector2D start_;
    Vector2D end_;
};
