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

Cuboid::Cuboid(Point nearest, Point farther):Figure(){
    
    for(unsigned int i=0; i<2; ++i){
        for(unsigned int j=0; j<2; ++j){
            for(unsigned int k=0; k<2; ++k){ this->vertexes[i][j][k] = Point(); }
        }
    }

    this->colour_ = {255,255,255};

    this->vertexes[0][0][0] = nearest;
    this->vertexes[1][1][1] = farther;

    this->calculate_vertexes();
}
//-------------------------------------------

//-----Methods-------------------------------
std::vector<unsigned char> Cuboid::get_colour(){
    std::vector<unsigned char> tmp = this->colour_;
    return tmp;
}

void Cuboid::calculate_vertexes(){
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

std::tuple<bool, double, bool> Cuboid::intersection(Point& P, Point& C, Point& L){
    std::tuple<bool, double, bool> parameters = {false, 1, false};

    // Вычисление точки пересечения
    Point M;
    Point m;
    double t=0.; // Параметр пересечения
    double temp_t = 0.; // Временный параметр пересечения, который будем считать
    int surf=0; // Номер плоскости, в котором лежит точка 
    
    for(int i=0, k=0, l=0, inter=0; i<6; ++i){
    
        // Вводим ещё параметр k для того, чтобы отследить самое первое пересечение
        // точки с какой-либо гранью'

        // Мы вводим параметр l потому что нужно пройтись по координатам точек
        // и координат всего три: я не знаю, как сделать так, чтобы он обращался нормально
        // когда i>=3
        if(i<3){l=i;}
        else{l=i-3;}

        // Здесь условие на то, что знаменатель не обратиться в нуль. Это означает, что либо точки лежат в одной плоскости,
        // либо прямая параллельна плоскости
        if( std::abs(P[l]-C[l])<=std::max(std::abs(P[l]),std::abs(C[l]))*DBL_EPSILON ){ continue; }

        temp_t = ((*edges_[i][0])[l] - P[l])/(P[l]-C[l]); 

        if(temp_t < 0.){ continue; }
        else if( temp_t == 0.){ 
            inter = true; 
            
            t = temp_t;
            M = m;
            ++k;
            std::get<0>(parameters) = true;
            // Может быть тут стоит добавить условие, что temp_t<t? Но посмотрим, что будет на практике
        }

        // Вычисление точки на параллелепипеде
        for(int j=0; j<3; ++j){
            m[j] = P[j] + temp_t*(P[j]-C[j]);

            // Здесь почему-то двойное неравенство ломалось на тех случаях, когда 8>=8 && 8<=8
            // поэтому я в добавок ещё расписал условие равенства на каждый случай:
            // ( m[j] >= (*edges_[i][0])[j] && m[j] <= (*edges_[i][1])[j] ) || m[j] == (*edges_[i][0])[j]) || m[j] == (*edges_[i][1])[j])
            if( (m[j] > (*edges_[i][0])[j] && m[j] < (*edges_[i][1])[j]) ||
                std::abs(m[j]-(*edges_[i][0])[j]) <= std::max(std::abs(m[j]),std::abs((*edges_[i][0])[j]))*DBL_EPSILON ||
                std::abs(m[j]-(*edges_[i][1])[j]) <= std::max(std::abs(m[j]),std::abs((*edges_[i][1])[j]))*DBL_EPSILON
            ){ inter = true; }
            else{ inter = false; break; }
            // ПРАВИЛЬНО СРАВНИВАТЬ С ЭПСИЛОНОМ НА <= !!!!!!!
        }

        // Далее нужно сохранить параметр
        // Логика довольно простая с точки зрения ангема:
        // имеем параметр t, который является количественной мерой расстояния до объекта
        // с помощью вектора CP. Проще говоря, есть точка, до которой нужно ехать 5*CP
        // векторов и есть ещё 7*CP. Логично, что ближе будет 5*CP
        if(inter == true && (k==0 || temp_t<t)){  
            t = temp_t;
            M = m;
            ++k;
            std::get<0>(parameters) = true;
            surf = i;
        }
    }

    std::vector<double> light={L[0]-M[0],L[1]-M[1],L[2]-M[2]};
    if(std::get<0>(parameters) == 1){
        // Тут поработаем с тенями
        switch(surf){
            case 0: std::get<1>(parameters) = dot_product({-1,0,0}, light);
            case 1: std::get<1>(parameters) = dot_product({0,-1,0}, light);
            case 2: std::get<1>(parameters) = dot_product({0,0,-1}, light);
            case 3: std::get<1>(parameters) = dot_product({1,0,0}, light);
            case 4: std::get<1>(parameters) = dot_product({0,1,0}, light);
            case 5: std::get<1>(parameters) = dot_product({0,0,1}, light);
        }
    }
    
    return parameters;
}
//-------------------------------------------