/**
 * @file DronePath.h
 * DronePath class
 */
#ifndef ROTATION3D_DRONEPATH_H
#define ROTATION3D_DRONEPATH_H

#include <deque>
#include "Constants.h"
#include "Drawable.h"

class Scene;
class AutoDrone;

class DronePath : public Drawable
{
private:
    std::deque<FlyStates> moves;
    const AutoDrone& drone;
    const Scene& scene;
protected:
    void fillAscentMoves();
    void fillLandingMoves();
    void fillFlyingMoves(double distance);
    void fillRotateMoves(double angle);
public:
    DronePath(const AutoDrone& _drone, const Scene& _scene);
    FlyStates getNextMove();
    void makeMoves(double angle, double distance);
    std::list<std::string> getDrawString() const override;
};

#endif //ROTATION3D_DRONEPATH_H
