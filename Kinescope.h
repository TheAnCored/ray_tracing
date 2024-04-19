#pragma once

#include <iostream>
#include <vector>

#include "Screen.h"
#include "Point.h"

class Kinescope: protected Screen{
protected:
    Point point_of_view; // perspective projection

    double screen_distance; // between point of view and screen
    double angle_of_vision; // on the screen

    double limit_of_visibility; // by the point_of_view

public:
    //------Constructors-----------------
    // Empty
    Kinescope();
    // With all data
    Kinescope(Point point_of_view, uint pheight, uint pwidth, double distance, double angle, double limit_of_visibility, vect norm_vect, vect rotation);
    //-----------------------------------

    //------Methods----------------------
    
    //-----------------------------------
};