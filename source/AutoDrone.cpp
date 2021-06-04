/**
 * @file AutoDrone.cpp
 * Definition of AutoDrone class
 */
#include "AutoDrone.h"
#include "Constants.h"
#include "VectorAction.h"

/**
 * Parametric constructor
 * @param x position in x axis
 * @param y position in y axis
 */
AutoDrone::AutoDrone(double x, double y) : Drone(x, y), flying(false)
{
}

/** Spin propellers while drone flying */
void AutoDrone::spinPropellers()
{
    Drone::operator[](0).spin(-PROPELLER_SPEED);
    Drone::operator[](1).spin(PROPELLER_SPEED);
    Drone::operator[](2).spin(-PROPELLER_SPEED);
    Drone::operator[](3).spin(PROPELLER_SPEED);
}

/** Move drone up  */
void AutoDrone::moveUp()
{
    spinPropellers();
    move({0, 0, SPEED});
}

/** Move drone down */
void AutoDrone::moveDown()
{
    spinPropellers();
    move({0, 0, -SPEED});
}

/** Move drone straight */
void AutoDrone::moveStraight()
{
    using namespace VectorAction;
    auto dir = getDirection();
    move(dir/abs(dir) * SPEED);
}

/** Rotate drone right and spin propellers */
void AutoDrone::rotateRight()
{
    Drone::operator[](0).spin(-PROPELLER_SPEED / 2);
    Drone::operator[](3).spin(PROPELLER_SPEED / 2);
    spin(-SPEED);
}

/** Rotate drone left and spin propellers */
void AutoDrone::rotateLeft()
{
    Drone::operator[](1).spin(PROPELLER_SPEED / 2);
    Drone::operator[](2).spin(-PROPELLER_SPEED / 2);
    spin(SPEED);
}

/** Flying method */
void AutoDrone::fly()
{
    rotateLeft();
}
