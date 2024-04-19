#include "Sphere.h"

//------Constructors----------------------------------
Sphere::Sphere():Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = 1;
    this->colour_ = {255, 255, 255};
}

Sphere::Sphere(Point& center):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }

    this->radius_ = 1;
    this->colour_ = {255, 255, 255};
}

Sphere::Sphere(double radius):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = radius;
    this->colour_ = {255, 255, 255};
}

Sphere::Sphere(std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = 1;
    this->colour_ = colour;
}

Sphere::Sphere(double radius, Point& center):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }

    this->radius_ = radius;
    this->colour_ = { 255, 255, 255};
}

Sphere::Sphere(double radius, std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = radius;
    this->colour_ = colour;    
}

Sphere::Sphere(Point& center, std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }
    
    this->radius_ = 1;
    this->colour_ = colour;      
}

Sphere::Sphere(double radius, Point& center, std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }

    this->radius_ = radius;
    this->colour_ = colour;    
};
//----------------------------------------------------

//------Methods---------------------------------------
