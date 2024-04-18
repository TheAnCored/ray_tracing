#include "Kinescope.h"

//------Constructors------------------
Kinescope::Kinescope():Screen(){}

Kinescope::Kinescope(Point pnt, uint ph, uint pw, double dist, 
                    double angle, double limit, vect norm, vect rot):
                    Screen(ph, pw, dist, angle, norm, rot)
{
    this->point_of_view = pnt;
    this->screen_distance = dist;
    this->angle_of_vision = angle;
    this->limit_of_visibility = limit;
}