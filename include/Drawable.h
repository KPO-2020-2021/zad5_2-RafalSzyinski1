/**
 * @file Drawable.h
 * Base class designed to be able to draw objects
 */
#ifndef ROTATION3D_DRAWABLE_H
#define ROTATION3D_DRAWABLE_H

#include <string>
#include <vector>

class Drawable
{
private:
    std::string color;
public:
    Drawable();
    explicit Drawable(std::string _color);
    void changeColor(std::string _color);
    std::string getParallelogramString(const std::vector<double>& sP, const std::vector<double>& a, const std::vector<double>& b) const;
    std::string getTriangleString(const std::vector<double>& sP, const std::vector<double>& a, const std::vector<double>& b) const;
    std::string getLineString(const std::vector<double>& sP, const std::vector<double>& eP) const;
    virtual std::string getDrawString() const;
};

#endif //ROTATION3D_DRAWABLE_H
