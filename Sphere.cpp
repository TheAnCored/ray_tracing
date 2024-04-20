#include "Sphere.h"

//------Constructors----------------------------------
Sphere::Sphere():Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = 1;
    this->colour_ = {255, 255, 255};
}

Sphere::Sphere(Point& center):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }

    this->radius_ = 1;
    this->colour_ = {255, 255, 255};
}

Sphere::Sphere(double radius):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = radius;
    this->colour_ = {255, 255, 255};
}

Sphere::Sphere(std::vector<unsigned char> colour):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = 1;
    this->colour_ = colour;
}

Sphere::Sphere(double radius, Point& center):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = center[i]; }

    this->radius_ = radius;
    this->colour_ = { 255, 255, 255};
}

Sphere::Sphere(double radius, std::vector<unsigned char> colour):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = 0.; }

    this->radius_ = radius;
    this->colour_ = colour;    
}

Sphere::Sphere(Point& center, std::vector<unsigned char> colour):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = center[i];}
    
    this->radius_ = 1;
    this->colour_ = colour;      
}

Sphere::Sphere(double radius, Point& center, std::vector<unsigned char> colour):Figure(){
    for(int i=0; i<3; ++i){ this->center_[i] = center[i];}

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
    Point M; // On sphere

    std::vector<double> CP = {P[0]-C[0], P[1]-C[1], P[2]-C[2]}; 
    std::vector<double> CO = {center_[0]-C[0], center_[1]-C[1], center_[2]-C[2]};

    double dot_CP_CO = dot_product(CP, CO);
    double dot_CP_CP = dot_product(CP, CP);
    double dot_CO_CO = dot_product(CO, CO);

    double discriminant = 0.0f;

    // Проверка на отрицательность дискриминанта
    {
        double tmp = dot_CO_CO-radius_*radius_;
        if(tmp < 0){ return 0; }
    }

    discriminant = 4*dot_CP_CO*dot_CP_CO - 4*dot_CP_CP*(dot_CO_CO-radius_*radius_);

    double parameter = 0.0f, parameter1 = 0.0f, parameter2 = 0.0f;

    if(discriminant == 0){ 
        parameter = dot_CP_CO/dot_CP_CP; 

        for(int i=0; i<3; ++i){
            M[i] = C[i] + parameter*CP[i];
        }
        // Здесь ещё должны быть лучи света!

        return 1;
    }
    else if(discriminant>0){
        /*
        Мы здесь выбираем один из двух возможных корней. Сразу будем отсекать отрицательные корни, потому что они находятся 
        за экраном. Если оба корня отрицательны - просто возвращаем 0. 

        Если меньший параметр parameter2 будет более либо равен нулю, то сразу берём его, т.к. второй по значению всегда больше
        Если второй меньше нуля, то берём положительный первый.
        */
        parameter1 = (2*dot_CP_CO + sqrt(discriminant))/(2*dot_CP_CP);
        parameter2 = (2*dot_CP_CO - sqrt(discriminant))/(2*dot_CP_CP);

        if(parameter2 >= 0){
            parameter = parameter2;
            
            for(int i=0; i<3; ++i){
                M[i] = C[i] + parameter*CP[i];
            }
            // Тут код по расчёту оттенка
            

            return 1;
        }
        else if(parameter2 < 0 && parameter1 >= 0){
            parameter = parameter1;
            
            for(int i=0; i<3; ++i){
                M[i] = C[i] + parameter*CP[i];
            }
            // Тут код по расчёту оттенка


            return 1;
        }
    }

    return 0;
}