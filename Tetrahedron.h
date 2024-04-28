#pragma once

#include "Figure.h"

using arr = std::array<std::array<std::shared_ptr<Point>, 3>, 4>;

class Tetr:public Figure{
private:
    arr vertexes;

public:
//------ Constructors ----------------------
    Tetr();

    Tetr(Point&,Point&,Point&,Point&);

//------------------------------------------

//------ Methods ---------------------------
    //
    virtual std::tuple<bool, double, bool, double> intersection(Point& pixel, Point& cam, Point& light);
//------------------------------------------
}; 