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

/// Length of propeller = sqrt(3) * PROPELLER_WIDTH
constexpr double PROPELLER_LENGTH = 1.732050807568877 * PROPELLER_WIDTH;

/// Drone height
constexpr double DRONE_HEIGHT = 10;

/// Drone width
constexpr double DRONE_WIDTH = 15;

/// Drone length
constexpr double DRONE_LENGTH = 20;

#endif //ROTATION3D_CONSTANTS_H
