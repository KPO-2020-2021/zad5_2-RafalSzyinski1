/**
 * @file Scene.cpp
 * Definition of Scene class
 */
#include "Scene.h"

#include <iostream>
#include <chrono>

/** Parametric constructor */
Scene::Scene() : plt(), objects(), drones(), option(Options::NONE)
{
    Cuboid temp({20, 0, 0}, {0, 20, 0}, {0, 0, 20}, {5, 5, 0});
    temp.changeColor("#FF00FF");
    addCuboid(temp);

    Plane temp2(Plane({10, 0, 0}, {0, 10, 0}, {5, 0, 5}, {-10, -10, 0}));
    temp2.changeColor("#555555");
    addPlane(temp2);

    addTetrahedron(Tetrahedron({10, 0, 0}, {0, 10, 0}, {0, 0, 30}, {20, -5, 0}));

    auto* ad = new AutoDrone(-20, 20, *this);
    ad->changeColor("#777777");
    drones.push_back(std::shared_ptr<AutoDrone>(ad));

    t1 = std::thread([this] { return getOption(option); });
}

/** Destructor of Scene */
Scene::~Scene()
{
    t1.join();
}

/** Static method to read input from user in another thread */
void Scene::getOption(Options& option)
{
    while (option != Options::EXIT)
    {
        printMenu();
        char opt;
        std::cin >> opt;
        switch (opt)
        {
            case '0':
                option = Options::EXIT;
                break;
            default:
                option = Options::NONE;
                break;
        }
    }
}

/** Static method to print menu with all options */
void Scene::printMenu()
{
    std::cout << "Menu: " << std::endl
              << "0 - Exit" << std::endl;
}

/** Drawing method */
void Scene::draw()
{
    for (auto& i : objects)
        plt.add(*i);
    for (auto& i : drones)
        plt.add(*i);

    plt.drawAndClear();
}

/** Add Plane to objects */
void Scene::addPlane(const Plane& plane)
{
    objects.push_back(std::make_shared<Plane>(plane));
}

/** Add Pyramid to objects */
void Scene::addPyramid(const Pyramid& pyramid)
{
    objects.push_back(std::make_shared<Pyramid>(pyramid));
}

/** Add Cuboid to objects */
void Scene::addCuboid(const Cuboid& cuboid)
{
    objects.push_back(std::make_shared<Cuboid>(cuboid));
}

/** Add Tetrahedron to objects */
void Scene::addTetrahedron(const Tetrahedron& tetra)
{
    objects.push_back(std::make_shared<Tetrahedron>(tetra));
}

/** Main loop */
void Scene::run()
{
    while (true)
    {
        draw();

        for (auto& i : drones)
            i->fly(20, 100);

        if (option == Options::EXIT)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}