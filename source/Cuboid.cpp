#include "Cuboid.h"

Cuboid::Cuboid(std::vector<double> _x, std::vector<double> _y, std::vector<double> _z, std::vector<double> _sP)
        : Figure(std::move(_x), std::move(_y), std::move(_z), std::move(_sP))
{

}

std::string Cuboid::getDrawString() const
{
    return Drawable::getDrawString();
}