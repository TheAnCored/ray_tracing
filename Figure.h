#include <tuple>
#include <iostream>
#include <vector>
#include <array>

#pragma once

#include "Point.h"

using array3d = std::array<std::array<std::array<Point, 2>, 2>, 2>;

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