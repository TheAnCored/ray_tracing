#include <iostream>
#include <memory>
#include <cstdarg>
#include <omp.h>

#pragma once

#define N 3

class Point{
private:    
    std::unique_ptr<double[]> point;
public:
//------Constructors-------------------------
    Point(); // Empty

    // All coordinates in array
    Point(std::unique_ptr<double[]>); 
    Point(std::shared_ptr<double[]>); 

    // All coordinates like arg
    Point(int, ...);

    // Copy constructor
    Point(const Point&);

    // Move constructor
    Point(Point&&);

//-------------------------------------------
//------Operators----------------------------
    // Op[]
    double& operator[](int);
    double& operator[](int) const;

    // Op+
    Point& operator+(Point&);
    std::shared_ptr<Point> operator+(std::shared_ptr<Point>);

    // Op-
    Point& operator-(Point&);
    std::shared_ptr<Point> operator-(std::shared_ptr<Point>);

    // Op=
    Point& operator=(const Point&);
    Point& operator=(Point&&);
//-------------------------------------------
//------Methods------------------------------

    // Перезапись всей точки
    void write(std::shared_ptr<double[]>);
    void write(std::unique_ptr<double[]>);
//-------------------------------------------

//------Destructors--------------------------
    ~Point()=default;
//-------------------------------------------
};