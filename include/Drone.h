/**
 * @file Drone.h
 * Drone class
 */
#ifndef ROTATION3D_DRONE_H
#define ROTATION3D_DRONE_H

#include "Cuboid.h"
#include "Propeller.h"

class Drone : public Cuboid
{
private:
    std::vector<Propeller> propellers;
public:
    explicit Drone(double x = 0, double y = 0);
    std::list<std::string> getDrawString() const override;
    void spin(double angle);
    void move(const std::vector<double>& vec);
    std::vector<double> getPosition() const;
    const std::vector<double>& getDirection() const;
    Propeller& operator[](int index);
};


#endif //ROTATION3D_DRONE_H
