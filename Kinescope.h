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
    // Empty
    Kinescope();
    /* All data:    
        1. point_of_view, 
        2. pheight, 
        3. pwidth, 
        4. distance, 
        5. angle,
        6. limit_of_visibility, 
        7. normal vect,
        8. angle_of_rotation
    */
    Kinescope(Point, uint, uint, double, double, double, vect, vect);
};