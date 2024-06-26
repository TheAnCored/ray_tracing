#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <cfloat>

#include "Point.h"

using array3d = std::array<std::array<std::array<Point, 2>, 2>, 2>;

class Figure{
protected:
    std::vector<unsigned char> colour_;

public:
//-----Constructors---------------------------------
    // Empty
    Figure();

    // Colour
    Figure(unsigned char R, unsigned char G, unsigned char B);
//--------------------------------------------------
//------Methods-------------------------------------
    // Get-function
    std::vector<unsigned char> get_colour();

    // Set colour of figure
    void set_colour(unsigned char, unsigned char, unsigned char);
    
    void set_r(unsigned char);
    void set_g(unsigned char);
    void set_b(unsigned char);

    // the intersection of a ray and a shape
    virtual std::tuple<bool, double, double, double> intersection(Point& pixel, Point& cam, Point& light)=0;

    //------Operators----------------
};

double dot_product(std::vector<double>, std::vector<double>);
std::vector<double> cross_product(std::vector<double>, std::vector<double>);