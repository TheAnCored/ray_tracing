#include "header.h"

int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    // Данные задачи
    Point point_of_view(-2,12,4); // Точка, с которой мы будем смотреть на пространство
    std::vector<double> direction_of_view{1.5,-2,-1}; // Направление, куда будем смотреть
    std::vector<double> rotation{0,0,1}; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
    Point light_point{9,20,5};
    double screen_distance{2.5}; // Расстояние между точкой зрения и экраном
    double limit_of_visibility{40}; // Граница видимости, отчитываемая ОТ ТОЧКИ ЗРЕНИЯ
    double angle_of_view{60}; // Угол обзора в радианах 
    std::array<unsigned int,2> screen_size{5000,5000}; // Размеры экрана в пикселях: первая координата - ширина, вторая - высота
    
    Kinescope kin(point_of_view, screen_size[0], screen_size[1], screen_distance, angle_of_view, limit_of_visibility, direction_of_view, rotation, light_point);

    Point center(2,3,-4);

    Point a(4,-4,0);
    Point c(4,4,0);
    Point b(10,3,-1);
    Point d(8,0,5);

    //std::shared_ptr<Sphere> sp1 = std::make_shared<Sphere>(4 ,center);
    std::shared_ptr<Tetr> tetr1 = std::make_shared<Tetr>(a,b,c,d);
   // std::vector<std::shared_ptr<Figure>> figure;

    //figure.push_back(tetr1);
    //figure.push_back(sp1);

    kin.get_image(tetr1);

    return 0;
}