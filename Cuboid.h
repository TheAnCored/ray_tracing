#include "Figure.h"

#pragma once

using edge = std::array<std::array<std::shared_ptr<Point>,4>, 6>;

class Cuboid: public Figure{

protected:
    // Here are points is vertexes of rectangular cuboid
    array3d vertexes; 
    
    // Грани параллелепипеда
    edge edges_;
public:
//-----Constructors--------------------------    
    Cuboid(); // Empty
    // Two opposite points of cuboid
    Cuboid(Point, Point);
//-------------------------------------------

//-----Methods-------------------------------
    // This is a method that allows you to find all the vertices of a cuboid by two opposite
    void calculate_vertexes();
    void calculate_edge();

    virtual std::tuple<bool, double, bool> intersection(Point& pixel, Point& cam, Point& light);
//-------------------------------------------
};