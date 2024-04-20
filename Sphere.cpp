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

Sphere::Sphere(std::vector<unsigned char> colour):Figure(){
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

Sphere::Sphere(double radius, std::vector<unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = radius;
    this->colour_ = colour;    
}

Sphere::Sphere(Point& center, std::vector<unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }
    
    this->radius_ = 1;
    this->colour_ = colour;      
}

Sphere::Sphere(double radius, Point& center, std::vector<unsigned char> colour):Figure(){
    //#pragma omp parallel for
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }

    this->radius_ = radius;
    this->colour_ = colour;    
};
//----------------------------------------------------

//------Methods---------------------------------------
void Sphere::set_colour(unsigned char R, unsigned char G, unsigned char B){ this->colour_ = { R, G, B}; }

std::vector<unsigned char> Sphere::get_colour(){ 
    std::vector<unsigned char> tmp = this->colour_;
    return tmp;
}

bool Sphere::intersection(Point& P, Point& C){
    std::vector<double> CP = {P[0]-C[0], P[1]-C[1], P[2]-C[2]}; 
    std::vector<double> CO = {center_[0]-C[0], center_[1]-C[1], center_[2]-C[2]};

    double dot_prod = dot_product(CP, CO);

    std::vector<double> normCO = {CO[0] - dot_prod*CP[0], CO[1] - dot_prod*CP[1], CO[2] - dot_prod*CP[2]};

    double len_normCO = sqrt(dot_product(normCO,normCO));

    if(std::abs(len_normCO - radius_) <= std::fmax(std::abs(len_normCO), std::abs(radius_))*DBL_EPSILON){ return 1; }
    return 0;
}