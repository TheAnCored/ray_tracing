#include "header.h"


int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    // Данные задачи
    Point point_of_view; // Точка, с которой мы будем смотреть на пространство
    std::vector<double> direction_of_view; // Направление, куда будем смотреть
    std::vector<double> angle_of_rotation; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
    double length; // Расстояние между точкой зрения и экраном
    double limit_of_visibility; // Граница видимости, отчитываемая ОТ ТОЧКИ ЗРЕНИЯ
    double angle_of_view; // Угол обзора в радианах 
    std::array<int,2> screen_size; // Размеры экрана в пикселях
    Point light; // Свет

    Point center;
    Sphere sph(center,{254,12,123});
    Cuboid cube;


    return 0;
}