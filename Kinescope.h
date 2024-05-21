#pragma once

#include <iostream>
#include <vector>

#include "Disp.h"
#include "Point.h"
#include "Figure.h"
#include "Sphere.h"
#include "CImg.h"
#include "Cuboid.h"
#include "Tetrahedron.h"

class Kinescope: public Disp{
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
    void set_camera(Point); void set_camera(double, double, double);
    void set_normal(std::vector<double>); void set_normal(double, double, double);
    void set_rotation(std::vector<double>); void set_rotation(double, double, double);
    void set_screen_distance(double);
    void set_limit(double);
    void set_angle_of_view(double);
    void set_light(Point);

    void setup();

    // Images
    void get_image(std::shared_ptr<Sphere>);
    void get_image(std::shared_ptr<Tetr>);
    void get_image(std::shared_ptr<Cuboid>);

    void get_image(std::vector<std::shared_ptr<Figure>>);
    
    void convert_to_bmp();
    //-----------------------------------
};