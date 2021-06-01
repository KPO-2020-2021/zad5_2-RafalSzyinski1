/**
 * @file Drawable.cpp
 * Definition of Drawable class
 */

#include "Drawable.h"
#include "VectorAction.h"

#include <sstream>

/// Default constructor set color to red
Drawable::Drawable() : color("#FF0000")
{
}

/// Parametric constructor
Drawable::Drawable(std::string _color)
{
    changeColor(std::move(_color));
}

/**
 * Change object color
 * @param _color in hex format e.g. #FF00FF
 * @throw std::invalid_argument when color is the wrong format
 */
void Drawable::changeColor(std::string _color)
{
    if (_color.size() != 7)
        throw std::invalid_argument("Wrong format of color");
    if (_color[0] != '#')
        throw std::invalid_argument("Wrong format of color");

    for (auto& i : _color)
        if ((i > 70 || i < 65) && (i > 57 || i < 57))
            throw std::invalid_argument("Wrong format of color");
    color = _color;
}

/**
 * Draw parallelogram in gnuplot \n Use VectorAction.h
 * @param sP start point
 * @param a first vector starting in sP
 * @param b second vector starting in sP
 * @return string for gnuplot
 */
std::string Drawable::getParallelogramString(const std::vector<double>& sP, const std::vector<double>& a, const std::vector<double>& b) const
{
    using namespace VectorAction;
    std::stringstream ss;
    ss << "polygon from " << sP << " to " << (sP + a) << " to " << (sP + a + b) << " to " << (sP + b) << " to " << sP;
    ss << getDrawString();
    return ss.str();
}

/**
 * Draw triangle in gnuplot \n Use VectorAction.h
 * @param sP start point
 * @param a first vector starting in sP
 * @param b second vector starting in sP
 * @return string for gnuplot
 */
std::string Drawable::getTriangleString(const std::vector<double>& sP, const std::vector<double>& a,
                                        const std::vector<double>& b) const
{
    using namespace VectorAction;
    std::stringstream ss;
    ss << "polygon from " << sP << " to " << (sP + a) << " to " << (sP + b) << " to " << sP;
    ss << getDrawString();
    return ss.str();
}

/**
 * Draw line in gnuplot \n Use VectorAction.h
 * @param sP start point
 * @param eP end point
 * @return string for gnuplot
 */
std::string Drawable::getLineString(const std::vector<double>& sP, const std::vector<double>& eP) const
{
    using namespace VectorAction;
    std::stringstream ss;
    ss << "polygon from " << sP << " to " << eP << " to " << -sP;
    ss << getDrawString();
    return ss.str();
}

/// @return style of object \n
std::string Drawable::getDrawString() const
{
    return R"(fs border lc "#000000" transparent solid fc rgb ")" + color + "\"";
}