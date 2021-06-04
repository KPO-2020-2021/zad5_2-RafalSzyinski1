/**
 * @file DronePath.cpp
 * Definition of DronePath class
 */
#include "DronePath.h"
#include "AutoDrone.h"
#include "MatrixAction.h"

#include <stdexcept>

/**
 * Parametric constructor
 * @param _drone owner
 * @param _scene scene with all objects
 */
DronePath::DronePath(const AutoDrone& _drone, const Scene& _scene) : drone(_drone), scene(_scene)
{
}

/**
 * Use in AutoDrone
 * @return move which AutoDrone have to make
 */
FlyStates DronePath::getNextMove()
{
    if (moves.empty())
        throw std::out_of_range("DronePath: no moves");
    auto ret = moves.front();
    moves.pop_front();
    return ret;
}

/**
 * Create path for drone
 * @param angle angle of fly
 * @param distance distance of fly
 */
void DronePath::makeMoves(double angle, double distance)
{
    fillAscentMoves();
    fillRotateMoves(angle);
    fillFlyingMoves(distance);
    fillLandingMoves();
    moves.push_back(FlyStates::END);
}

/** Fill ascent moves */
void DronePath::fillAscentMoves()
{
    double times = (MAX_ALTITUDE - drone.getPosition().at(2)) / SPEED;
    for (int i = 0; i < times; ++i)
        moves.push_back(FlyStates::ASCENT);
}

/** Fill landing moves */
void DronePath::fillLandingMoves()
{
    // TODO poprawic
    double times = (MAX_ALTITUDE - DRONE_HEIGHT / 2) / SPEED;
    for (int i = 0; i < times; ++i)
        moves.push_back(FlyStates::LANDING);
}

/** Fill flying straight moves */
void DronePath::fillFlyingMoves(double distance)
{
    double times = (distance) / SPEED;
    for (int i = 0; i < times; ++i)
        moves.push_back(FlyStates::FLYING);
}

/** Fill rotate moves */
void DronePath::fillRotateMoves(double angle)
{
    angle = angle - (360 *  (int)(angle/360));
    if (angle < 0)
        angle = 360 + angle;
    if (angle > 180)
    {
        angle = angle - 180;
        double times = angle / SPEED;
        for (int i = 0; i < times; ++i)
            moves.push_back(FlyStates::ROTATE_LEFT);
    }
    else
    {
        double times = angle / SPEED;
        for (int i = 0; i < times; ++i)
            moves.push_back(FlyStates::ROTATE_RIGHT);
    }
}

/**
 * Override method to draw object in gnuplot \n Use VectorAction.h and MatrixAction.h
 * @return list of object to draw
 */
std::list<std::string> DronePath::getDrawString() const
{
    using namespace MatrixAction;
    using namespace VectorAction;
    auto pos = drone.getPosition();
    auto dir = drone.getDirection();
    std::list<std::string> ret;
    matrix<double> left({
        {std::cos(M_PI/180.0 * SPEED),-std::sin(M_PI/180.0 * SPEED), 0},
         {std::sin(M_PI/180.0 * SPEED), std::cos(M_PI/180.0 * SPEED), 0},
         {0, 0, 1}});

    matrix<double> right({
         {std::cos(M_PI/180.0 * -SPEED),-std::sin(M_PI/180.0 * -SPEED), 0},
         {std::sin(M_PI/180.0 * -SPEED), std::cos(M_PI/180.0 * -SPEED), 0},
         {0, 0, 1}});

    double count = 0;
    FlyStates countingState = FlyStates::NONE;
    for (auto& i : moves)
    {
       if (i == countingState)
           ++count;
       else
       {
           switch (countingState)
           {
               case FlyStates::ASCENT:
                   ret.push_back(getLineString(pos, pos + std::vector<double>({0, 0, SPEED * count})));
                   pos = pos + std::vector<double>({0, 0, SPEED * count});
                   break;
               case FlyStates::FLYING:
                   ret.push_back(getLineString(pos, pos + (dir/abs(dir) * SPEED * count)));
                   pos = pos + (dir/abs(dir) * SPEED * count);
                   break;
               case FlyStates::LANDING:
                   ret.push_back(getLineString(pos,  std::vector<double>({0, 0, SPEED * count})));
                   //pos = pos - std::vector<double>({0, 0, SPEED * count});
                   break;
               case FlyStates::ROTATE_LEFT:
                   for (int i = 0; i < count; ++i)
                        dir = left * dir;
                   break;
               case FlyStates::ROTATE_RIGHT:
                   for (int i = 0; i < count; ++i)
                       dir = right * dir;
                   break;
           }
           count = 1;
           countingState = i;
       }
    }
    return ret;
}

