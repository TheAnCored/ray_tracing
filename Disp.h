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
using pixels = std::vector<std::vector<std::vector<unsigned char>>>; // enumerate pixels like an elements in matrix

class Disp{
protected:
    // vertical is height, horizontal is width
    psize screen_psize_; // in PIXEL
    double pixel_size_; // in double
    size screen_size_; // in double

    // ----- DIRECTIONS --------------
    vect direction_of_view_; // Направление, куда будем смотреть
    vect rotation_; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления

    // ----- PIXEL -------------
    pixels pixel_; // Пиксели экрана
public:
    // Empty
    Disp();

    // With size
    Disp(uint pheight, uint pwidth);
    Disp(uint pheight, uint pwidth, double distance, double angle);
    Disp(uint pheight, uint pwidth, double distance, double angle, vect norm, vect rot);

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
    void setup(double distance, double angle); 

    // ph,pw,d,an
    void setup(uint pheight, uint pwidth, double distance, double angle);
};