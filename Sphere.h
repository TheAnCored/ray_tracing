#include "Figure.h"

#pragma once

class Sphere: protected Figure{
private:
    std::shared_ptr<Point> center;
    double radius;

public:
//------Constructors-------------------------
    Sphere(); // Empty
    // Center's coordinates
    Sphere(Point&);
    // Radius of sphere
    Sphere(double);
    // Sphere's colour
    Sphere(std::tuple<unsigned char, unsigned char, unsigned char>);

    // radius+center
    Sphere(double, Point&);
    // radius+colour
    Sphere(double, std::tuple<unsigned char, unsigned char, unsigned char>);
    // center+colour
    Sphere(Point&, std::tuple<unsigned char, unsigned char, unsigned char>);
    // All data
    Sphere(double, Point&, std::tuple<unsigned char, unsigned char, unsigned char>);
//--------------------------------------------

//------Methods-------------------------------
    void set_colour(unsigned char, unsigned char, unsigned char);
}; 