#include "header.h"

int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    // Данные задачи
    Point point_of_view(0,0,0); // Точка, с которой мы будем смотреть на пространство
    std::vector<double> direction_of_view{1,0,0}; // Направление, куда будем смотреть
    std::vector<double> rotation{0,0,1}; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
    double screen_distance{10}; // Расстояние между точкой зрения и экраном
    double limit_of_visibility{35}; // Граница видимости, отчитываемая ОТ ТОЧКИ ЗРЕНИЯ
    double angle_of_view{60}; // Угол обзора в радианах 
    std::array<unsigned int,2> screen_size{100, 200}; // Размеры экрана в пикселях: первая координата - ширина, вторая - высота
    Point light; // Свет
    
    Kinescope kin(point_of_view, screen_size[0], screen_size[1], screen_distance, angle_of_view, limit_of_visibility, direction_of_view, rotation);

    Point center;
    Sphere sph(center, {254,12,123});

    Point near(1,1,1);
    Point far(10,10,10);
    //Cuboid cub;

    return 0;
}