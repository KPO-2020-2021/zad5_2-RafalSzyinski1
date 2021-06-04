#ifndef ROTATION3D_SCENE_H
#define ROTATION3D_SCENE_H

#include "AutoDrone.h"
#include "Plane.h"
#include "Cuboid.h"
#include "Tetrahedron.h"
#include "Pyramid.h"
#include "Plot.h"
#include "Constants.h"

#include <memory>
#include <thread>

class Scene
{
private:
    std::list<std::shared_ptr<Figure> > objects;
    std::list<AutoDrone> drones;
    Plot plt;
    Options option;
    std::thread t1;

    friend class DronePath;

    static void getOption(Options& option);
    static void printMenu();
public:
    Scene();
    ~Scene();
    void run();
    void draw();

    void addPlane(const Plane& plane);
    void addPyramid(const Pyramid& pyramid);
    void addCuboid(const Cuboid& cuboid);
    void addTetrahedron(const Tetrahedron& tetra);

};


#endif //ROTATION3D_SCENE_H
