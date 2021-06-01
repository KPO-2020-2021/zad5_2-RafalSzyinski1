/**
 * @file Figure.h
 * Base class of each figure
 */
#ifndef ROTATION3D_FIGURE_H
#define ROTATION3D_FIGURE_H

#include "Drawable.h"

class Figure : public Drawable
{
private:
    friend class Transform;
protected:
    std::vector<double> sP;
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> z;
public:
    Figure() = delete;
    Figure(std::vector<double> _x, std::vector<double> _y, std::vector<double> _z, std::vector<double> _sP = {0, 0, 0});
    std::vector<double> getCenterOfMass() const;
    friend bool operator==(const Figure& fig1, const Figure& fig2);
    std::string getDrawString() const override = 0;
};


#endif //ROTATION3D_FIGURE_H
