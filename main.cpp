#include "header.h"

int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    // Данные задачи
    Point point_of_view(0,0,0); // Точка, с которой мы будем смотреть на пространство
    std::vector<double> direction_of_view{1,0,0}; // Направление, куда будем смотреть
    std::vector<double> rotation{0,0,1}; // Обобщённый вектор, обозначающий угол поворота экрана отн-но направления
    std::vector<double> light_point{0,5,5};
    double screen_distance{2.5}; // Расстояние между точкой зрения и экраном
    double limit_of_visibility{40}; // Граница видимости, отчитываемая ОТ ТОЧКИ ЗРЕНИЯ
    double angle_of_view{90}; // Угол обзора в радианах 
    std::array<unsigned int,2> screen_size{1000, 1000}; // Размеры экрана в пикселях: первая координата - ширина, вторая - высота
    Point light; // Свет
    
    Kinescope kin(point_of_view, screen_size[0], screen_size[1], screen_distance, angle_of_view, limit_of_visibility, direction_of_view, rotation);
    
    Point center(6,0,0);

    std::vector<unsigned char> colour = {255, 255, 255};

    std::shared_ptr<Sphere> figure = std::make_shared<Sphere>(2 ,center, colour);
    kin.get_image(figure);

    return 0;
}