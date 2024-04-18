#include "Sphere.h"

//------Constructors----------------------------------
Sphere::Sphere():Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = 0.; }

    this->radius = 1;
    this->colour = {255, 255, 255};
}

Sphere::Sphere(Point& center):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = center[i]; }

    this->radius = 1;
    this->colour = {255, 255, 255};
}

Sphere::Sphere(double radius):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = 0.; }

    this->radius = radius;
    this->colour = {255, 255, 255};
}

Sphere::Sphere(std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = 0.; }

    this->radius = 1;
    this->colour = colour;
}

Sphere::Sphere(double radius, Point& center):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = center[i]; }

    this->radius = radius;
    this->colour = colour;
}

Sphere::Sphere(double radius, std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = 0.; }

    this->radius = radius;
    this->colour = colour;    
}

Sphere::Sphere(Point& center, std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = center[i]; }

    this->radius = 1;
    this->colour = colour;      
}

Sphere::Sphere(double radius, Point& center, std::tuple<unsigned char, unsigned char, unsigned char> colour):Figure(){
    #pragma omp parallel for
    for(int i=0; i<N; ++i){ (*this->center)[i] = center[i]; }

    this->radius = radius;
    this->colour = colour;    
};
//----------------------------------------------------

//------Methods---------------------------------------
