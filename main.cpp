#include "header.h"


int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    // Данные задачи
    Point point_of_view; // Точка, с которой мы будем смотреть на пространство
    std::vector<double> direction_of_view; // Направление, куда будем смотреть
    std::vector<double> angle_of_rotation; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
    double screen_distance; // Расстояние между точкой зрения и экраном
    double limit_of_visibility; // Граница видимости, отчитываемая ОТ ТОЧКИ ЗРЕНИЯ
    double angle_of_view; // Угол обзора в радианах 
    std::array<unsigned int,2> screen_size; // Размеры экрана в пикселях: первая координата - ширина, вторая - высота
    Point light; // Свет

    Point center;
    Sphere sph(center, {254,12,123});

    Point near(1,1,1);
    Point far(10,10,10);
    Cuboid cube(near, far);


    return 0;
}