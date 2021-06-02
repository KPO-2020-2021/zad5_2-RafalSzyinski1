/**
 * @file Plot.cpp
 * Definition of Plot class
 */
#include "Plot.h"

/**
 * Add figure to drawing objects
 * @param fig figure to draw
 */
void Plot::add(const Drawable& fig)
{
    auto obj = fig.getDrawString();
    for (auto& i : obj)
        objects.push_back(" set object " + std::to_string(objects.size() + 1) + " " + i);
}


/** Draw every object which add with add method and clear them */
void Plot::drawAndClear()
{
    sendcommand("set xyplane at 0");
    sendcommand("set xrange [-60:60]");
    sendcommand("set yrange [-60:60]");
    sendcommand("set zrange [-60:60]");
    sendcommand("unset border");
    sendcommand("unset tics");

    for (auto& i : objects)
        sendcommand(i);

    sendcommand(R"(splot 0 lc "#00000000" notitle)");
    objects.clear();
}

