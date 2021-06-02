#include "Plot.h"

Plot::Plot() : Gnuplot(), objects()
{
}

void Plot::add(const Drawable& fig)
{
    auto obj = fig.getDrawString();
    for (auto& i : obj)
        objects.push_back(" set object " + std::to_string(objects.size() + 1) + " " + i);
}

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

