#include "header.h"

int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    // Данные задачи
    Point point_of_view(-4,10,12); // Точка, с которой мы будем смотреть на пространство
    std::vector<double> direction_of_view{4,-4,-4}; // Направление, куда будем смотреть
    std::vector<double> rotation{0,0,1}; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
    Point light_point{9,20,5};
    double screen_distance{2.5}; // Расстояние между точкой зрения и экраном
    double limit_of_visibility{40}; // Граница видимости, отчитываемая ОТ ТОЧКИ ЗРЕНИЯ
    double angle_of_view{60}; // Угол обзора в радианах 
    std::array<unsigned int,2> screen_size{3000,3000}; // Размеры экрана в пикселях: первая координата - ширина, вторая - высота
    
    Kinescope kin(point_of_view, screen_size[0], screen_size[1], screen_distance, angle_of_view, limit_of_visibility, direction_of_view, rotation, light_point);

    Point center(5,0,0);

    std::vector<unsigned char> colour = {255, 255, 255};

    Point a(8,-4,-2);
    Point b(10,4,2);
    // std::shared_ptr<Sphere> figure = std::make_shared<Sphere>(3 ,center, colour);
    std::shared_ptr<Cuboid> figure = std::make_shared<Cuboid>(a,b);
    kin.get_image(figure);

    return 0;
}