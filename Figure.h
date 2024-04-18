#include <tuple>
#include <iostream>
#include <vector>

#pragma once

#include "Point.h"

using space = std::vector<std::vector<std::vector<Point>>>;
using plane = std::vector<std::vector<Point>>;
using line = std::vector<Point>;

class Figure{
protected:
    std::tuple<unsigned char, unsigned char, unsigned char> colour;

public:
//-----Constructors---------------------------------
    // Empty
    Figure();

    // Colour
    Figure(unsigned char, unsigned char, unsigned char);
//--------------------------------------------------
//------Methods-------------------------------------
    // Set colour of figure
    void set_colour(unsigned char, unsigned char, unsigned char);
    void set_r(unsigned char);
    void set_g(unsigned char);
    void set_b(unsigned char);

    // the intersection of a ray and a shape
    //bool intetsection();
};

double dot_product(std::vector<double>, std::vector<double>);