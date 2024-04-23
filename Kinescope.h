#pragma once

#include <iostream>
#include <vector>

#include "Disp.h"
#include "Point.h"
#include "Figure.h"
#include "Sphere.h"
#include "CImg.h"
#include "Cuboid.h"

class Kinescope: protected Disp{
protected:
    Point point_of_view_; // perspective projection

    double screen_distance_; // between point of view and screen
    double angle_of_vision_; // on the screen

    double limit_of_visibility_; // by the point_of_view

    Point light_;
public:
    //------Constructors-----------------
    // Empty
    Kinescope();
    // Without light
    Kinescope(Point point_of_view, uint pheight, uint pwidth, double distance, 
                    double angle, double limit_of_visibility, vect norm_vect, vect rotation);

    // With light
    Kinescope(Point pnt, uint ph, uint pw, double dist, 
                    double angle, double limit, vect norm, vect rot, Point light);
    //-----------------------------------

    //------Methods----------------------
    void get_image(std::shared_ptr<Sphere>);
    void get_image(std::vector<std::shared_ptr<Figure>>);
    void get_image(std::shared_ptr<Cuboid>);
    void convert_to_bmp();
    //-----------------------------------
};