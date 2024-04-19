#include <tuple>
#include <iostream>
#include <vector>
#include <array>

#pragma once

#include "Point.h"

using array3d = std::array<std::array<std::array<Point, 2>, 2>, 2>;

class Figure{
protected:
    std::tuple<unsigned int, unsigned int, unsigned int> colour_;

public:
//-----Constructors---------------------------------
    // Empty
    Figure();

    // Colour
    Figure(unsigned int, unsigned int, unsigned int);
//--------------------------------------------------
//------Methods-------------------------------------
    // Set colour of figure
    void set_colour(unsigned int, unsigned int, unsigned int);
    void set_r(unsigned int);
    void set_g(unsigned int);
    void set_b(unsigned int);

    // the intersection of a ray and a shape
    //bool intetsection();
};

double dot_product(std::vector<double>, std::vector<double>);