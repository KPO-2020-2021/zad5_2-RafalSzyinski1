#include "Cuboid.h"
#include "Pyramid.h"
#include "Plane.h"
#include "Drone.h"
#include "Tetrahedron.h"
#include "Transform.h"
#include "Plot.h"

#include <thread>
#include <chrono>

int main()
{
    Plot a;
    //Tetrahedron b({20, 0, 0}, {0, 20, 0}, {0, 0, 20}, {1, 1, 1});
    Drone c(20, 20);
    //Transform::scaleToCenterOfMass(b, 2);
    while (true)
    {
       // a.add(b);
        a.add(c);
        c.spin(2);
        c.move({0.01, 0.01, 0.01});
        //Transform::rotateAroundCenterOfMass(b, 2);
        a.drawAndClear();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

    return 0;
}