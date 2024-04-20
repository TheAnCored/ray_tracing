#pragma once

#include <iostream>
#include <vector>

#include "Disp.h"
#include "Point.h"
#include "Figure.h"
//#include "CImg.h"

class Kinescope: protected Disp{
protected:
    Point point_of_view_; // perspective projection

    double screen_distance_; // between point of view and screen
    double angle_of_vision_; // on the screen

    double limit_of_visibility_; // by the point_of_view

public:
    //------Constructors-----------------
    // Empty
    Kinescope();
    // With all data
    Kinescope(Point point_of_view, uint pheight, uint pwidth, double distance, double angle, double limit_of_visibility, vect norm_vect, vect rotation);
    //-----------------------------------

    //------Methods----------------------
    void get_image(std::shared_ptr<Figure>);
    void convert_to_bmp();
    //-----------------------------------
};