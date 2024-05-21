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

std::tuple<bool, double, double, double> Sphere::intersection(Point& P, Point& C, Point& L){
    Point M; // On sphere

    std::vector<double> CP = {P[0]-C[0], P[1]-C[1], P[2]-C[2]}; 
    std::vector<double> CO = {center_[0]-C[0], center_[1]-C[1], center_[2]-C[2]};

    double dot_CP_CO = dot_product(CP, CO);
    double dot_CP_CP = dot_product(CP, CP);
    double dot_CO_CO = dot_product(CO, CO);

    double discriminant = 0.;

    // Проверка на отрицательность дискриминанта
    {
        double tmp = dot_CO_CO-radius_*radius_;
        if(tmp < 0){ return std::tuple<bool, double, double, double>{0,0,0,0}; }
    }

    discriminant = 4*dot_CP_CO*dot_CP_CO - 4*dot_CP_CP*(dot_CO_CO-radius_*radius_);

    double parameter = 0.;

    std::tuple<bool, double, double, double> temp{0 ,0.,0.,0.};

    if(discriminant >= 0){
            
        if(discriminant>0){
            /*
            Мы здесь выбираем один из двух возможных корней. Сразу будем отсекать отрицательные корни, потому что они находятся 
            за экраном. Если оба корня отрицательны - просто возвращаем 0. 

            Если меньший параметр parameter2 будет более либо равен нулю, то сразу берём его, т.к. второй по значению всегда больше
            Если второй меньше нуля, то берём положительный первый.
            */
            double parameter1 = 0., parameter2 = 0.;
            parameter1 = (2*dot_CP_CO + sqrt(discriminant))/(2*dot_CP_CP);
            parameter2 = (2*dot_CP_CO - sqrt(discriminant))/(2*dot_CP_CP);

            if(parameter2 >= 0){
                parameter = parameter2;
            }
            else if(parameter2 < 0 && parameter1 >= 0){
                parameter = parameter1;
            }
        }

        for(int i=0; i<3; ++i){
            M[i] = C[i] + parameter*CP[i];
        }

        // Найдем нормаль в точке касания и единичный вектор из точки касания к свету
        std::vector<double> ML(3, 0.); // Вектор, соединяющий точку пресечения и свет
        std::vector<double> OM(3, 0.); // Нормаль к поверхности
        double norm_ML=0., norm_OM=0.;

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

        // Параметры пикселя:
        // 1) Пересечение с фигурой луча
        // 2) Скалярное произведение между нормалью и точкой фигуры и света
        // 3) Отражение по модели Фонга
        // 4) Расстояние
        // Вычисление косинуса угла между двумя векторами
        
        double dot_ML_OM = 0.;
        for(int i=0; i<3; ++i){
            dot_ML_OM += ML[i]*OM[i];
        }

        temp = {true, dot_ML_OM, 0, parameter};

        // Вычислим координаты вектора, противоположнонаправленного к отраженному лучу света
        // и также сразу найдём его влияние на освещение
        if(std::get<1>(temp)>0.){
            std::vector<double> tau(3, 0.); 
            std::vector<double> MC(3, 0.);
            std::vector<double> LM(3, 0.);
            
            for(int i=0; i<3; ++i){
                MC[i] = -CP[i];
                LM[i] = -ML[i]; 
            }

            double module_MC = sqrt(dot_product(MC,MC));
            double module_LM = sqrt(dot_product(LM,LM));
            
            for(int i=0; i<3; ++i){ 
                MC[i] /= module_MC;
                LM[i] /= module_LM;
            }   
            double dot_LM_n = dot_product(LM, OM);

            // Нахождение отражённого вектора
            for(int i=0; i<3; ++i){
                tau[i] = LM[i] - 2*dot_LM_n*OM[i];
            }

            // Далее ищем коэффициент для блика
            std::get<2>(temp) = pow(dot_product(MC, tau), 100);
        }
    }

    return temp;
}