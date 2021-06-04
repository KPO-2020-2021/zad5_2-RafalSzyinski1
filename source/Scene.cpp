#include "Scene.h"

#include <iostream>

#include <chrono>
Scene::Scene() : plt(), objects(), drones(), option(Options::NONE)
{
    Cuboid temp({20, 0, 0}, {0, 20, 0}, {0, 0, 20}, {5, 5, 0});
    temp.changeColor("#FF00FF");
    addCuboid(temp);

    Plane temp2(Plane({10, 0, 0}, {0, 10, 0}, {5, 0, 5}, {-10, -10, 0}));
    temp2.changeColor("#555555");
    addPlane(temp2);

    addTetrahedron(Tetrahedron({10, 0, 0}, {0, 10, 0}, {0, 0, 30}, {20, -5, 0}));

    AutoDrone ad(-20, 20);
    ad.changeColor("#777777");
    drones.emplace_back(ad);

    t1 = std::thread([this] { return getOption(option); });
}

Scene::~Scene()
{
    t1.join();
}

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


void Scene::printMenu()
{
    std::cout << "Menu: " << std::endl
              << "0 - Exit" << std::endl;
}

void Scene::draw()
{
    for (auto& i : objects)
        plt.add(*i);
    for (auto& i : drones)
        plt.add(i);

    plt.drawAndClear();
}

void Scene::addPlane(const Plane& plane)
{
    objects.push_back(std::make_shared<Plane>(plane));
}

void Scene::addPyramid(const Pyramid& pyramid)
{
    objects.push_back(std::make_shared<Pyramid>(pyramid));
}

void Scene::addCuboid(const Cuboid& cuboid)
{
    objects.push_back(std::make_shared<Cuboid>(cuboid));
}

void Scene::addTetrahedron(const Tetrahedron& tetra)
{
    objects.push_back(std::make_shared<Tetrahedron>(tetra));
}

void Scene::run()
{
    while (true)
    {
        drones.back().fly();
        draw();
        if (option == Options::EXIT)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}