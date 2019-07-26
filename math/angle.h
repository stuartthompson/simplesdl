#pragma once

#include <math.h>

const double M_PI_OVER_180 = M_PI / 180;
const double M_180_OVER_PI = 180 / M_PI;

/**
 * Converts degrees to radians.
 */
template <typename T>
const float degreesToRadians(const T degrees) { return degrees * M_PI_OVER_180; }

/**
 * Converts radians to degrees.
 */
template <typename T>
const float radiansToDegrees(const T radians) { return radians * M_180_OVER_PI; }