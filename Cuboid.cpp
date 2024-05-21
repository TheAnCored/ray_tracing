#include "Cuboid.h"

//-----Constructors--------------------------
Cuboid::Cuboid():Figure(){
    for(unsigned int i=0; i<2; ++i){
        for(unsigned int j=0; j<2; ++j){
            for(unsigned int k=0; k<2; ++k){ this->vertexes[i][j][k] = Point(); }
        }
    }

    this->colour_ = {255,255,255};
}

Cuboid::Cuboid(Point a, Point b):Figure(){
    
    for(unsigned int i=0; i<2; ++i){
        for(unsigned int j=0; j<2; ++j){
            for(unsigned int k=0; k<2; ++k){ this->vertexes[i][j][k] = Point(); }
        }
    }

    this->colour_ = {255,255,255};

    this->vertexes[0][0][0] = a;
    this->vertexes[1][1][1] = b;

    this->calculate_vertexes();
}
//-------------------------------------------

//-----Methods-------------------------------
void Cuboid::calculate_vertexes(){
    // --------------------- 1 --------------------------------
    /* Поправка к алгоритму: я сделал вычисления, построенные на идеальных данных.
    Если будут даны противоположные точки для параллелепипеда, то тогда нужно ещё найти максимальную и минимальную точки.
    */
    Point A = vertexes[0][0][0]; Point B = vertexes[1][1][1];
    std::vector<double> AB = {B[0]-A[0],B[1]-A[1],B[2]-A[2]};
    
    // Простой алгоритм нахождения минимальной и максимальной точек параллелепипеда
    #pragma omp parallel for
    for(int i=0; i<3; ++i){ 
        if(AB[i] < 0){ B[i] += (-1)*AB[i]; A[i] += AB[i]; }
    }
    vertexes[0][0][0] = A; vertexes[1][1][1] = B;

    // --------------------- 2 --------------------------------
    double delta_x = vertexes[1][1][1][0] - vertexes[0][0][0][0]; 
    double delta_y = vertexes[1][1][1][1] - vertexes[0][0][0][1];

    // Здесь постепенно по нумерации точек прибавляем по нужной координате:  
    // всего необходимо определить шесть точек

    // Нижняя грань
    this->vertexes[1][0][0] = this->vertexes[0][0][0]; this->vertexes[1][0][0][0] += delta_x;
    this->vertexes[0][1][0] = this->vertexes[0][0][0]; this->vertexes[0][1][0][1] += delta_y; 

    this->vertexes[1][1][0] = this->vertexes[0][0][0]; this->vertexes[1][1][0][0] += delta_x; this->vertexes[1][1][0][1] += delta_y; 
    
    // Верхняя грань
    this->vertexes[0][0][1] = this->vertexes[1][1][1]; this->vertexes[0][0][1][0] -= delta_x; this->vertexes[0][0][1][1] -= delta_y;
    
    this->vertexes[1][0][1] = this->vertexes[1][1][1]; this->vertexes[1][0][1][1] -= delta_y;
    this->vertexes[0][1][1] = this->vertexes[1][1][1]; this->vertexes[0][1][1][0] -= delta_x; 

    this->calculate_edge();
}

void Cuboid::calculate_edge(){

    //----------------------------------------------------------------------
    // НЕ МЕНЯТЬ ПОРЯДОК ПЛОСКОСТЕЙ, ИНАЧЕ АЛГОРИТМ ПОИСКА ТОЧКИ ПЕРЕСЕЧЕНИЯ
    //                          !!!! СЛОМАЕТСЯ !!!!
    //----------------------------------------------------------------------

    // Здесь нулевая компонента - это минимальная точка грани
    // Единица - максимальная точка грани

    // OYZ
    edges_[0][0] = std::make_shared<Point>(vertexes[0][0][0]);
    edges_[0][1] = std::make_shared<Point>(vertexes[0][1][1]);

    // OXZ
    edges_[1][0] = edges_[0][0];
    edges_[1][1] = std::make_shared<Point>(vertexes[1][0][1]);

    // OXY
    edges_[2][0] = edges_[0][0];
    edges_[2][1] = std::make_shared<Point>(vertexes[1][1][0]);

    // OYZ-1
    edges_[3][0] = std::make_shared<Point>(vertexes[1][0][0]);
    edges_[3][1] = std::make_shared<Point>(vertexes[1][1][1]);

    // OXZ-1
    edges_[4][0] = std::make_shared<Point>(vertexes[0][1][0]);
    edges_[4][1] = edges_[3][1]; 

    // OXY-1
    edges_[5][0] = std::make_shared<Point>(vertexes[0][0][1]);
    edges_[5][1] = edges_[3][1];

}

std::tuple<bool, double, double,double> Cuboid::intersection(Point& P, Point& C, Point& L){
    std::tuple<bool, double, double, double> parameters = {false, 1, 0., 0.};

    // Вычисление точки пересечения
    Point M;

    double t=0.; // Параметр пересечения
    double temp_t = 0.; // Временный параметр пересечения, который будем считать
    int surf=0; // Номер плоскости, в котором лежит точка 
    
    // Проходка по каждой грани параллелепипеда
    for(int i=0,k=0, l=0, inter=0; i<6; ++i){
    
        // Вводим ещё параметр k для того, чтобы отследить самое первое пересечение
        // точки с какой-либо гранью'

        // Мы вводим параметр l потому что нужно пройтись по координатам точек
        // и координат всего три: я не знаю, как сделать так, чтобы он обращался нормально
        // когда i>=3
        if(i<3){l=i;}
        else{l=i-3;}

        // Здесь условие на то, что знаменатель не обратиться в нуль. Это означает, что либо точки лежат в одной плоскости,
        // либо прямая параллельна плоскости
        if( std::abs(P[l]-C[l])<=std::max(std::abs(P[l]),std::abs(C[l]))*FLT_EPSILON ){ continue; }

        // Случай, когда точка грани совпала с пикселем
        if(std::abs((*edges_[i][0])[l] - P[l])<=std::max(std::abs((*edges_[i][0])[l]),std::abs(P[l]))*DBL_EPSILON){
            t = ((*edges_[i][0])[l] - P[l])/(P[l]-C[l]); // Вычислсяем параметр
            
            // Вычисляем точку пересечения
            M = P;

            // Записываем нужные параметры
            std::get<0>(parameters) = true;
            surf = i;
            ++k;

            continue;
        }

        // Вычисляем параметр
        temp_t = ((*edges_[i][0])[l] - P[l])/(P[l]-C[l]); 
        
        // Логично, что случай меньше нуля сразу отбросим, т.к. точка находится за экраном 
        if(temp_t < 0.){ continue; }

        Point m; // Временная точка 
        // Вычисление точки на параллелепипеде
        for(int j=0; j<3; ++j){
            m[j] = P[j] + temp_t*(P[j]-C[j]);

            // Здесь почему-то двойное неравенство ломалось на тех случаях, когда 8>=8 && 8<=8
            // поэтому я в добавок ещё расписал условие равенства на каждый случай:
            // ( m[j] >= (*edges_[i][0])[j] && m[j] <= (*edges_[i][1])[j] ) || m[j] == (*edges_[i][0])[j]) || m[j] == (*edges_[i][1])[j])
            // Также ломалось условие при слишком малых разницах, поэтому применил FLT_EPSILON
            if(m[j] >= (*edges_[i][0])[j] && m[j] <= (*edges_[i][1])[j]){ inter = true; }
            else if(std::abs(m[j]-(*edges_[i][0])[j]) <= std::max(std::abs(m[j]),std::abs((*edges_[i][0])[j]))*std::numeric_limits<float>::epsilon()){ inter = true; }
            else if(std::abs(m[j]-(*edges_[i][1])[j]) <= std::max(std::abs(m[j]),std::abs((*edges_[i][1])[j]))*std::numeric_limits<float>::epsilon()){ inter = true; }
            else{ 
                inter = false; 
                break; 
            }
            // ПРАВИЛЬНО СРАВНИВАТЬ С ЭПСИЛОНОМ НА <= !!!!!!!
            // также иногда нужно использовать FLT_EPSILON
        }

        // Далее нужно сохранить параметр
        // Логика довольно простая с точки зрения ангема:
        // имеем параметр t, который является количественной мерой расстояния до объекта
        // с помощью вектора CP. Проще говоря, есть точка, до которой нужно ехать 5*CP
        // векторов и есть ещё 7*CP. Логично, что ближе будет 5*CP
        if(inter == true){  
            if( k == 0 ){
                t = temp_t;
                M = m;
                std::get<0>(parameters) = true;
                std::get<3>(parameters) = t;
                surf = i;
            }
            else if( temp_t < t){
                t = temp_t;
                M = m;
                std::get<0>(parameters) = true;
                std::get<3>(parameters) = t;
                surf = i;
            }
            ++k;
        }
    }

    // Далее смотрим параметр
    if(std::get<0>(parameters) == 1){
        std::vector<double> light={L[0]-M[0],L[1]-M[1],L[2]-M[2]}; // Вектор в сторону точки света от точки на фигуре

        // Нормировка этого же вектора
        for(int j=0; j<3; ++j){
            light[j] /= sqrt(dot_product(light,light));
        }

        // Тут поработаем с тенями
        double temp_dot=0.; // Этот параметр нужен для того, чтобы проверить на отрицательность скалярное произведение

        // Далее идёт выбор стороны нормали
        switch(surf){
            case 0: 
                temp_dot = dot_product({-1,0,0}, light); 
                if(temp_dot >= 0){
                    std::get<1>(parameters) = dot_product({-1,0,0}, light); 
                }else{ std::get<1>(parameters) = 0.; }
                break;

            case 1: 
                temp_dot = dot_product({0,-1,0}, light); 
                if(temp_dot >= 0){
                    std::get<1>(parameters) = dot_product({0,-1,0}, light); 
                }else{ std::get<1>(parameters) = 0.; }
                break;

            case 2: 
                temp_dot = dot_product({0,0,-1}, light); 
                if(temp_dot > 0.){
                    std::get<1>(parameters) = dot_product({0,0,-1}, light); 
                }else{ std::get<1>(parameters) = 0.; }
                break;

            case 3: 
                temp_dot = dot_product({1,0,0}, light); 
                if(temp_dot > 0.){
                    std::get<1>(parameters) = dot_product({1,0,0}, light); 
                }else{ std::get<1>(parameters) = 0.; }
                break;

            case 4: 
                temp_dot = dot_product({0,1,0}, light); 
                if(temp_dot > 0.){
                    std::get<1>(parameters) = dot_product({0,1,0}, light); 
                }else{ std::get<1>(parameters) = 0.; }
                break;

            case 5:
                temp_dot = dot_product({0,0,1}, light); 
                if(temp_dot > 0.){
                    std::get<1>(parameters) = dot_product({0,0,1}, light); 
                }else{ std::get<1>(parameters) = 0.; }
                break;
        }
    }

    return parameters;
}
//-------------------------------------------