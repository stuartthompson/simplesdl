#pragma once

/**
 * Represents a vector in 2D space.
 * 
 * A vector is stored as a point, which has an implicit direction and magnitude from the 2D origin.
 * In this way, a vector completely describes a point and can be used as a point when no heading or magnitude are needed.
 */
class Vector2D
{
public:
    /**
     * Initializes a vector with no magnitude.
     */
    Vector2D();
    
    /**
     * Initializes a vector from another vector.
     * 
     * @param vector The vector to initialize from.
     */
    Vector2D(const Vector2D& vector);

    /**
     * Initializes a vector from coordinates.
     * 
     * @param x The x coordinate of the vector.
     * @param y The y coordinate of the vector.
     */
    Vector2D(float x, float y);

    /**
     * Initializes a vector via its heading and magnitude.
     * 
     * @param heading The direction of the vector.
     * @param magnitude The length of the vector.
     */
	// Vector2D(const float heading, const float magnitude);

    /**
     * Sets the value of this vector.
     * 
     * @param vector The new vector value.
     * @return The updated vector.
     */
    Vector2D& operator=(const Vector2D& vector);

    // Arithmetic modifying operators
    Vector2D& operator+=(const Vector2D& vector);
    Vector2D& operator-=(const Vector2D& vector);
    Vector2D& operator*=(const Vector2D& vector);
    Vector2D& operator/=(const Vector2D& vector);

    // Arithmetic operators
    Vector2D operator+(const Vector2D& vector) const;
    Vector2D operator-(const Vector2D& vector) const;
    Vector2D operator*(const Vector2D& vector) const;
    Vector2D operator/(const Vector2D& vector) const;

    /**
     * Returns the heading of the vector.
     * This is the angle that describes the vector from the origin.
     */
	float heading() const;

    /**
     * Returns the magnitude (length) of the vector.
     */
	float magnitude() const;

    /**
     * Calculates the distance from another vector.
     * 
     * @param vector The vector to calculate the distance from.
     */
    float distanceFrom(const Vector2D& vector) const;

    // x and y coordinate of the vector
    float x, y; 
};
