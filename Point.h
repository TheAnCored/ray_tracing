#include <iostream>
#include <memory>
#include <cstdarg>

#pragma once

class Point{
private:    
    std::unique_ptr<double[]> point_;
public:
//------Constructors-------------------------
    Point(); // Empty

    // All coordinates in array
    Point(std::unique_ptr<double[]>); 
    Point(std::shared_ptr<double[]>); 

    // All coordinates like arg
    Point(double, double, double);

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
    Point operator+(const Point&)const;
    // Op-
    Point operator-(const Point&)const;

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