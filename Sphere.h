#include "Figure.h"
#include "Disp.h"

#pragma once

class Sphere: public Figure{
protected:
    Point center_;
    double radius_;

public:
//------Constructors-------------------------
    Sphere(); // Empty
    // Center's coordinates
    Sphere(Point&);
    // Radius of sphere
    Sphere(double);
    // Sphere's colour
    Sphere(std::vector<unsigned char>);

    // radius+center
    Sphere(double, Point&);
    // radius+colour
    Sphere(double, std::vector<unsigned char>);
    // center+colour
    Sphere(Point&, std::vector<unsigned char>);
    // All data
    Sphere(double, Point&, std::vector<unsigned char>);
//--------------------------------------------

//------Methods-------------------------------
    // Set-functions

    // Пересечение фигуры
    std::tuple<bool, double, bool, double> intersection(Point& P, Point& C, Point& L);

//------Operators-------------

}; 