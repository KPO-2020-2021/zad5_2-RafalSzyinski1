#include "Cuboid.h"
#include "Pyramid.h"
#include "Plane.h"
#include "Tetrahedron.h"
#include "Transform.h"
#include "Plot.h"

#include <thread>
#include <chrono>

int main()
{
    Plot a;
    Tetrahedron b({20, 0, 0}, {0, 20, 0}, {0, 0, 20}, {1, 1, 1});
    Transform::scaleToCenterOfMass(b, 2);
    double i = 0;
    while (true)
    {
        a.add(b);
        Transform::rotateAroundCenterOfMass(b, 2);
        a.drawAndClear();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i += 0.1;
    }

    return 0;
}