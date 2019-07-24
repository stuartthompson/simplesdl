#include <math.h>
#include "Angle.h"

const float M_PI_OVER_180 = M_PI / 180;
const float M_180_OVER_PI = 180 / M_PI;

// Degrees to Radians
const float degreesToRadians(const int degrees) {
    return degrees * M_PI_OVER_180;
}
const float degreesToRadians(const float degrees) {
    return degrees * M_PI_OVER_180;
}
const double degreesToRadians(const double degrees) {
    return degrees * M_PI_OVER_180;
}

// Radians to Degrees
const float radiansToDegrees(const int radians) {
    return radians * M_180_OVER_PI;
}
const float radiansToDegrees(const float radians) {
    return radians * M_180_OVER_PI;
}
const double radiansToDegrees(const double radians) {
    return radians * M_180_OVER_PI;
}
