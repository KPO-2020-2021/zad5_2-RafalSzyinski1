/**
 * @file Constants.h
 * Includes all constants form program
 */
#ifndef ROTATION3D_CONSTANTS_H
#define ROTATION3D_CONSTANTS_H

/// Minimum difference value of double to be considered equal
constexpr double EPSILON = 0.0000000001;

/// Height of propeller
constexpr double PROPELLER_HEIGHT = 4;

/// Width of propeller
constexpr double PROPELLER_WIDTH = 6;

/// Length of propeller
constexpr double PROPELLER_LENGTH = 1.732050807568877 * PROPELLER_WIDTH;

#endif //ROTATION3D_CONSTANTS_H
