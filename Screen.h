#pragma once

#include <iostream>
#include <cmath>
#include <array>
#include <vector>

#define PI 3.14159265
#define RAD(angle) angle*PI/180

using uint = unsigned int;
using size = std::array<double,2>;
using psize = std::array<unsigned int,2>;
using vect = std::vector<double>;

class Screen{
protected:
    // vertical is height, horizontal is width
    psize screen_psize;
    double pixel_size;
    size screen_size;

    vect direction_of_view; // Направление, куда будем смотреть
    vect rotation; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
public:
    // Empty
    Screen();

    // With size
    Screen(uint pheight, uint pwidth);
    Screen(uint pheight, uint pwidth, double distance, double angle);
    Screen(uint pheight, uint pwidth, double distance, double angle, vect norm, vect rot);

    //------ Methods -------
    // Get-functions
    int get_pwidth();
    int get_pheight();

    double get_width();
    double get_height();
    
    // Set-functions
    void set_pheight(unsigned int);
    void set_pwidth(unsigned int);

    void set_height(double);
    void set_width(double);
    
    // Setup function

    // distance, angle
    void setup(double, double); 

    // ph,pw,d,an
    void setup(uint,uint, double, double);
};