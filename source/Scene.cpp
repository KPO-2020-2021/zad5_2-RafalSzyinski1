/**
 * @file Scene.cpp
 * Definition of Scene class
 */
#include "Scene.h"
#include "Transform.h"

#include <iostream>
#include <chrono>


/** Static method to read input from user in another thread */
void Scene::getOption(Options& option)
{
    while (option != Options::EXIT)
    {
        while (option != Options::NONE)
            ;
        printMenu();
        char opt;
        std::cin >> opt;

        switch (opt)
        {
            case '0':
                option = Options::EXIT;
                break;
            case '1':
                option = Options::CHOOSE_DRONE;
                break;
            case '2':
                option = Options::GET_POS;
                break;
            case '3':
                option = Options::ADD_FIGURE;
                break;
            case '4':
                option = Options::DEL_FIGURE;
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
              << "0 - Exit" << std::endl
              << "1 - Choose drone" << std::endl
              << "2 - Get parameters of drones" << std::endl
              << "3 - Add figure" << std::endl
              << "4 - Delete figure" << std::endl;
}

/** Parametric constructor */
Scene::Scene() : plt(), objects(), drones(), option(Options::NONE)
{
    makeMarsArea();
    addDrones();
    t1 = std::thread([this] { return getOption(option); });
}

/** First option in Menu */
void Scene::chooseDrone()
{
    printDrones();
    int choose_drone;
    if (std::cin >> choose_drone)
    {
        if (choose_drone < 0 || choose_drone > drones.size())
        {
            std::cerr << "No such drone" << std::endl;
            return;
        }
        if (drones[choose_drone]->isFlying())
        {
            std::cerr << "Drone is already flying" << std::endl;
            return;
        }
        double ang, dis;
        std::cout << "Enter angle and distance: ";
        if (std::cin >> ang >> dis)
        {
            drones[choose_drone]->makePath(ang, dis);
        }
    }
}

/** Second option in Menu */
void Scene::printDrones() const
{
    for (int i = 0; i < drones.size(); ++i)
    {
        std::cout << "Drone " << i << ": (" << drones[i]->getPosition().at(0) << ", " << drones[i]->getPosition().at(1) << ") ";
        if (drones[i]->isFlying())
            std::cout << "is flying";
        std::cout << std::endl;
    }
}

/** Print all figures */
void Scene::printFigures() const
{
    int j = 0;
    for (auto& i : objects)
    {
        std::cout <<  typeid(*i).name()  << " " << j << ": (" << i->getPosition().at(0) << ", " << i->getPosition().at(1) << ")" << std::endl;
        ++j;
    }
}

/** Third option in Menu */
void Scene::addFigure()
{
    int choose = -1;
    std::cout << "0 - Cuboid" << std::endl;
    std::cout << "1 - Pyramid" << std::endl;
    std::cout << "2 - Plane" << std::endl;
    std::cout << "3 - Tetrahedron" << std::endl;
    if (std::cin >> choose)
    {
        double a, b, c;
        std::vector<double> x, y, z, sP;
        std::cout << "Enter x vector: ";
        std::cin >> a >> b >> c;
        x = {a, b, c};
        std::cout << "Enter y vector: ";
        std::cin >> a >> b >> c;
        y = {a, b, c};
        std::cout << "Enter z vector: ";
        std::cin >> a >> b >> c;
        z = {a, b, c};
        std::cout << "Enter starting point: ";
        std::cin >> a >> b >> c;
        sP = {a, b, c};
        switch (choose)
        {
            case 0:
                objects.push_back(std::make_shared<Cuboid>(Cuboid(x, y, z, sP)));
                break;
            case 1:
                objects.push_back(std::make_shared<Pyramid>(Pyramid(x, y, z, sP)));
                break;
            case 2:
                objects.push_back(std::make_shared<Plane>(Plane(x, y, z, sP)));
                break;
            case 3:
                objects.push_back(std::make_shared<Tetrahedron>(Tetrahedron(x, y, z, sP)));
                break;
            default:
                std::cerr << "No such option" << std::endl;
                break;
        }
    }
}

/** Fourth option in Menu */
void Scene::delFigure()
{
    printFigures();
    int choose;
    if (std::cin >> choose)
        if (choose < 0 || choose > objects.size())
            return;
    auto a = objects.begin();
    for (int i = 0; i < choose; ++i, ++a)
        ;
    objects.remove(*a);
}

/** Make nice area to fly */
void Scene::makeMarsArea()
{
    addCuboid(Cuboid({60, 0, 0}, {0, 60, 0}, {0, 0, 20}, {50, 40, 0}));
    Plane a({10, 0, 0}, {0, 60, 0}, {0, 0, 20}, {40, 40, 0});
    Transform::rotateAroundCenterOfMass(a, 180);
    addPlane(a);
    Transform::translate(a, std::vector<double>({35, -35, 0}));
    Transform::rotateAroundCenterOfMass(a, 90);
    addPlane(a);
    Transform::translate(a, std::vector<double>({35, 35, 0}));
    Transform::rotateAroundCenterOfMass(a, 90);
    addPlane(a);
    Transform::translate(a, std::vector<double>({-35, 35, 0}));
    Transform::rotateAroundCenterOfMass(a, 90);
    addPlane(a);

    addCuboid(Cuboid({40, 0, 0}, {0, 40, 0}, {0, 0, 80}, {MAP_SIZE - 40, 40 - MAP_SIZE, 0}));
    Pyramid b({{0, 0, 80}, {0, 40, 0}, {-100, 0, 0}, {MAP_SIZE - 40, 40 - MAP_SIZE, 0}});
    addPyramid(b);
    Plane c({40, 0, 0}, {0, 40, 0}, {0, 0, 80}, {MAP_SIZE - 40, 40 - MAP_SIZE, 0});
    Transform::rotateAroundCenterOfMass(c, 90);
    Transform::translate(c, std::vector<double>({0, 40, 0}));
    addPlane(c);
    Tetrahedron d({40, 0, 0}, {0, 40, 0}, {0, 0, 50}, {MAP_SIZE - 40, 40 - MAP_SIZE, 80});
    Transform::rotateAroundCenterOfMass(d, 90);
    addTetrahedron(d);

    addCuboid(Cuboid({100, 0, 0}, {0, 90, 0}, {0, 0, 20}, {-100, -90, 0}));
    addCuboid(Cuboid({30, 0, 0}, {0, 90, 0}, {0, 0, 70}, {-130, -90, 0}));
    addCuboid(Cuboid({130, 0, 0}, {0, 30, 0}, {0, 0, 70}, {-130, -120, 0}));
    Plane e({10, 0, 0}, {0, 90, 0}, {0, 0, 20}, {0, -90, 0});
    addPlane(e);
    Transform::rotateAroundCenterOfMass(e, 90);
    Transform::translate(e, std::vector<double>({-50, 50, 0}));
    addPlane(e);
    addPlane(Plane({30, 0, 0}, {0, 90, 0}, {0, 0, 50}, {{-100, -90, 20}}));
    Tetrahedron f({30, 0, 0}, {0, 30, 0}, {0, 0, 80}, {-(MAP_SIZE - 30), MAP_SIZE - 30, 0});
    Transform::rotateAroundCenterOfMass(f, 270);
    addTetrahedron(f);
}

/** Add drone to space */
void Scene::addDrones()
{
    auto* a = new AutoDrone(-30, 30, *this);
    a->changeColor("#FF0000");
    drones.push_back(std::shared_ptr<AutoDrone>(a));

    auto* b = new AutoDrone(-100, 30, *this);
    b->changeColor("#00FF00");
    drones.push_back(std::shared_ptr<AutoDrone>(b));

    auto* c = new AutoDrone(-65, 65, *this);
    c->changeColor("#0000FF");
    drones.push_back(std::shared_ptr<AutoDrone>(c));

}

/** Destructor of Scene */
Scene::~Scene()
{
    t1.join();
}

/** Main loop */
void Scene::run()
{
    while (true)
    {
        draw();

        for (auto& i : drones)
            i->fly();
        if (option == Options::EXIT)
        {
            break;
        }
        else if (option == Options::CHOOSE_DRONE)
        {
            chooseDrone();
            option = Options::NONE;
        }
        else if(option == Options::GET_POS)
        {
            printDrones();
            option = Options::NONE;
        }
        else if (option == Options::ADD_FIGURE)
        {
            addFigure();
            option = Options::NONE;
        }
        else if (option == Options::DEL_FIGURE)
        {
            delFigure();
            option = Options::NONE;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
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