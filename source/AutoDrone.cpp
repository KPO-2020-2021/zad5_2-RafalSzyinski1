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
AutoDrone::AutoDrone(double x, double y, const Scene& _scene) : Drone(x, y), flying(false), dronePath(*this, _scene)
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
void AutoDrone::fly(double angle, double distance)
{
    spinPropellers();
    if (!flying)
    {
        dronePath.makeMoves(angle, distance);
        flying = true;
    }
    else
    {
        switch (dronePath.getNextMove())
        {
            case FlyStates::NONE:
                break;
            case FlyStates::ASCENT:
                moveUp();
                break;
            case FlyStates::FLYING:
                moveStraight();
                break;
            case FlyStates::LANDING:
                moveDown();
                break;
            case FlyStates::ROTATE_LEFT:
                rotateLeft();
                break;
            case FlyStates::ROTATE_RIGHT:
                rotateRight();
                break;
            case FlyStates::STOP:
                break;
            case FlyStates::END:
                flying = false;
                break;
        }
    }
}

/**
 * Override method to draw object in gnuplot
 * @return list of object to draw
 */
std::list<std::string> AutoDrone::getDrawString() const
{
    auto ret = Drone::getDrawString();
    auto path = dronePath.getDrawString();
    ret.insert(ret.end(), path.begin(), path.end());
    return ret;
}
