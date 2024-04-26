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

std::tuple<bool, double, bool> Sphere::intersection(Point& P, Point& C, Point& L){
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
        if(tmp < 0){ return std::tuple<bool,double, double>{0,0,0}; }
    }

    discriminant = 4*dot_CP_CO*dot_CP_CO - 4*dot_CP_CP*(dot_CO_CO-radius_*radius_);

    double parameter = 0.0f, parameter1 = 0.0f, parameter2 = 0.0f;

    if(discriminant == 0){ 
        parameter = dot_CP_CO/dot_CP_CP; 

        for(int i=0; i<3; ++i){
            M[i] = C[i] + parameter*CP[i];
        }
        std::tuple<bool, double, bool> temp{1,0.f,0};

        return temp;
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
        }
        else if(parameter2 < 0 && parameter1 >= 0){
            parameter = parameter1;
        }
   
        for(int i=0; i<3; ++i){
            M[i] = C[i] + parameter*CP[i];
        }

        // Найдем нормаль в точке касания и единичный вектор из точки касания к свету
        std::vector<double> ML(3, 0.0f); // Вектор, соединяющий точку пресечения и свет
        std::vector<double> OM(3, 0.0f); // Нормаль к поверхности
        double norm_ML=0.0f, norm_OM=0.0f;

        // Вектор от точки пересечения к свету и его нормировка
        for(int i =0; i<3; ++i){        
            ML[i] = L[i] - M[i];
            OM[i] = M[i] - center_[i];
        }
        norm_ML = sqrt(dot_product(ML,ML));
        norm_OM = sqrt(dot_product(OM,OM));
        for(int i =0; i<3; ++i){        
            ML[i] /= norm_ML;
            OM[i] /= norm_OM;
        }

        // Вычисление косинуса угла между двумя векторами
        std::tuple<bool, double, bool> temp{1,dot_product(ML,OM),0};

        // Вычислим координаты вектора, противоположнонаправленного к отраженному лучу света
        // и также сразу найдём его влияние на освещение
        std::vector<double> norm_PC(3);
        std::vector<double> tau(3, 0.f); 

        double module = sqrt(dot_product(CP,CP));
        for(int i=0; i<3; ++i){ 
            norm_PC[i] = -CP[i]/module;

            tau[i] = (1+dot_product(ML,OM))*OM[i] - ML[i]; 
        }   
        
        if(std::abs(tau[0]-norm_PC[0])<std::max(std::abs(norm_PC[0]),std::abs(tau[0])*DBL_EPSILON) &&
           std::abs(tau[1]-norm_PC[1])<std::max(std::abs(norm_PC[1]),std::abs(tau[1])*DBL_EPSILON) &&
           std::abs(tau[2]-norm_PC[2])<std::max(std::abs(norm_PC[2]),std::abs(tau[2])*DBL_EPSILON)
        ){
            std::get<2>(temp) = 1;
        }

        return temp;
    }

    return {0,0,0};
}