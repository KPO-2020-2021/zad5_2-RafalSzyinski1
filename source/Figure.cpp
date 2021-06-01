/**
 * @file Figure.cpp
 * Definition of Figure class
 */
#include "Figure.h"
#include "VectorAction.h"

/**
 * Parametric constructor
 * @param _x x vector starting in sP
 * @param _y y vector starting in sP
 * @param _z z vector string in sP
 * @param _sP start point
 */
Figure::Figure(std::vector<double>  _x, std::vector<double>  _y, std::vector<double>  _z, std::vector<double>  _sP)
                : Drawable(), x(std::move(_x)), y(std::move(_y)), z(std::move(_z)), sP(std::move(_sP))
{
}

/**
 * Use VectorAction.h
 * @return center of mass figure
 */
std::vector<double> Figure::getCenterOfMass() const
{
    using VectorAction::operator+;
    using VectorAction::operator/;
    return (x + y + z) / 3.0;
}
