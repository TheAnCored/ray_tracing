#include "Figure.h"

#pragma once

class Sphere: protected Figure{
private:
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
    void set_colour(unsigned char, unsigned char, unsigned char);

    // Get-functions
    std::vector<unsigned char> get_colour() ;

    bool intersection(Point& P, Point& C);

//------Operators-------------

}; 