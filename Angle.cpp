#include <math.h>
#include "Angle.h"

/**
 * Converts degrees to radians.
 */
const float degreesToRadians(const float degrees) {
    return degrees * (M_PI / 180);
}

/**
 * Converts degrees to radians.
 */
const double degreesToRadians(const double degrees) {
    return degrees * (M_PI / 180);
}

/**
 * Converts radians to degrees.
 */
const float radiansToDegrees(const float radians) {
    return radians * (180 / M_PI);
}

/**
 * Converts radians to degrees.
 */
const double radiansToDegrees(const double radians) {
    return radians * (180 / M_PI);
}