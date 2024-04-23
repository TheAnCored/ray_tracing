#include "Kinescope.h"

//------Constructors------------------
Kinescope::Kinescope():Disp(){}

Kinescope::Kinescope(Point pnt, uint ph, uint pw, double dist, 
                    double angle, double limit, vect norm, vect rot):
                    Disp(ph, pw, dist, angle, norm, rot)
{
    this->point_of_view_ = pnt;
    this->screen_distance_ = dist;
    this->angle_of_vision_ = angle;
    this->limit_of_visibility_ = limit;
}

Kinescope::Kinescope(Point pnt, uint ph, uint pw, double dist, 
                    double angle, double limit, vect norm, vect rot, Point light):
                    Disp(ph, pw, dist, angle, norm, rot)
{
    this->point_of_view_ = pnt;
    this->screen_distance_ = dist;
    this->angle_of_vision_ = angle;
    this->limit_of_visibility_ = limit;
    this->light_ = light;
}
//------------------------------------

//------Methods-----------------------
void Kinescope::get_image(std::vector<std::shared_ptr<Figure>> figures){
 
    // 1 ---- Вычисление точки центра экрана
    Point D(
        point_of_view_[0] + screen_distance_*direction_of_view_[0],
        point_of_view_[1] + screen_distance_*direction_of_view_[1],
        point_of_view_[2] + screen_distance_*direction_of_view_[2]
        ); // Central point of screen

    // 2 ---- Вычисление точки B
    Point B(
        D[0] + rotation_[0]*(screen_size_[0]/2-pixel_size_/2),
        D[1] + rotation_[1]*(screen_size_[0]/2-pixel_size_/2),
        D[2] + rotation_[2]*(screen_size_[0]/2-pixel_size_/2)
    ); 
    
    // 3 ---- Вычисление ортогонального вектора [b,n]
    std::vector<double> tau = {
        rotation_[1]*direction_of_view_[2]-rotation_[2]*direction_of_view_[1],
        rotation_[2]*direction_of_view_[0]-rotation_[0]*direction_of_view_[2],
        rotation_[0]*direction_of_view_[1]-rotation_[1]*direction_of_view_[0]};

    // 4 ---- Вычисление точки p[0][0]
    Point start(
        B[0]+tau[0]*(screen_size_[1]/2 - pixel_size_/2),
        B[1]+tau[1]*(screen_size_[1]/2 - pixel_size_/2),
        B[2]+tau[2]*(screen_size_[1]/2 - pixel_size_/2)
    );


    // После получения отсчётной точки, начнём вычисление луче, которые будут 
    // проходить через центр пикселя и пересекать фигуру
    
    // 5 ---- Пройдёмся по каждому пикселю, чтобы получить 
    // самую ближнюю точку пересечения
    //unsigned int amount = figures.size();

    for(unsigned int i=0; i<screen_psize_[0]; ++i){
        for(unsigned int j=0; j<screen_psize_[1]; ++j){
            
            unsigned int amount = figures.size();

            // Проход по пересечениям фигуры
            for(unsigned int k=0; k < amount; ++i){
                std::tuple<bool, double, double> interns;
                interns = figures[k]->intersection(start, point_of_view_, this->light_);
                if(std::get<0>(interns)==1){
                    pixel_[i][j] = figures[k]->get_colour();

                    if(std::get<1>(interns)>=0){ 
                        for(int l=0; l<3; ++l){
                            pixel_[i][j][l] = pixel_[i][j][l]*std::get<1>(interns);
                        }
                    }else{ pixel_[i][j] = {0,0,0}; } 
                }else{ pixel_[i][j] = {119, 136, 153}; }
            }

            // В конце обязательно сделаем переход к соседнему cправа пикселю
            if(j < screen_psize_[1]-1){
                for(int k=0; k<3; ++k){ start[k] += (-1)*tau[k]*pixel_size_; }
            }
        }

        // Переход на следующую строку
        if(i < screen_psize_[0]-1){
            for(int k=0; k<3; ++k){ 
                start[k] += tau[k]*pixel_size_*(screen_psize_[1]-1); 
                start[k] += (-1)*rotation_[k]*pixel_size_;
            }
        }
    }

    // 6 ---- Конвертация изображения в bmp
    convert_to_bmp();
}

void Kinescope::get_image(std::shared_ptr<Cuboid> figure){

    // 1 ---- Вычисление точки центра экрана
    Point D(
        point_of_view_[0] + screen_distance_*direction_of_view_[0],
        point_of_view_[1] + screen_distance_*direction_of_view_[1],
        point_of_view_[2] + screen_distance_*direction_of_view_[2]
        ); // Central point of screen

    // 2 ---- Вычисление точки B
    Point B(
        D[0] + rotation_[0]*(screen_size_[0]/2-pixel_size_/2),
        D[1] + rotation_[1]*(screen_size_[0]/2-pixel_size_/2),
        D[2] + rotation_[2]*(screen_size_[0]/2-pixel_size_/2)
    ); 
    
    // 3 ---- Вычисление ортогонального вектора [b,n]
    std::vector<double> tau = {
        rotation_[1]*direction_of_view_[2]-rotation_[2]*direction_of_view_[1],
        rotation_[2]*direction_of_view_[0]-rotation_[0]*direction_of_view_[2],
        rotation_[0]*direction_of_view_[1]-rotation_[1]*direction_of_view_[0]};
    // Тут вектор должен получиться единичным, но из-за погрешностей - хз

    // 4 ---- Вычисление точки p[0][0]
    Point start(
        B[0]+tau[0]*(screen_size_[1]/2 - pixel_size_/2),
        B[1]+tau[1]*(screen_size_[1]/2 - pixel_size_/2),
        B[2]+tau[2]*(screen_size_[1]/2 - pixel_size_/2)
    );

    // После получения отсчётной точки, начнём вычисление луче, которые будут 
    // проходить через центр пикселя и пересекать фигуру

    // 5 ---- Пройдёмся по каждому пикселю, чтобы получить 
    // самую ближнюю точку пересечения
    for(unsigned int i=0; i<screen_psize_[0]; ++i){
        for(unsigned int j=0; j<screen_psize_[1]; ++j){

            
            // Проход по пересечениям фигуры
            std::tuple<bool, double, double> interns;
            //std::cout<<"[i]"<<i;
            //std::cout<<"[j]"<<j<<std::endl;

            interns = figure->intersection(start, point_of_view_, this->light_);

            if(std::get<0>(interns)==true){
                pixel_[i][j] = figure->get_colour();

                if(std::get<1>(interns)>=0 && std::get<2>(interns) == 0){ 
                    for(int l=0; l<3; ++l){
                        pixel_[i][j][l] = pixel_[i][j][l]*std::get<1>(interns);
                    }
                }
                //else if(std::get<0>(interns)==1 && std::get<2>(interns) == 1){ pixel_[i][j] = {255,255,255};}
                else{ pixel_[i][j] = {0,0,0}; }
            }else{ pixel_[i][j] = {119, 136, 153}; }
            

            // В конце обязательно сделаем переход к соседнему cправа пикселю
            if(j < screen_psize_[1]-1){
                for(int k=0; k<3; ++k){ start[k] += (-1)*tau[k]*pixel_size_; }
            }
        }

        // Переход на следующую строку
        if(i < screen_psize_[0]-1){
            for(int k=0; k<3; ++k){ 
                start[k] += tau[k]*pixel_size_*(screen_psize_[1]-1); 
                start[k] += (-1)*rotation_[k]*pixel_size_;
            }
        }
    }
    // 6 ---- Конвертация изображения в bmp
    convert_to_bmp();
}

void Kinescope::get_image(std::shared_ptr<Sphere> figure){

    // 1 ---- Вычисление точки центра экрана
    Point D(
        point_of_view_[0] + screen_distance_*direction_of_view_[0],
        point_of_view_[1] + screen_distance_*direction_of_view_[1],
        point_of_view_[2] + screen_distance_*direction_of_view_[2]
        ); // Central point of screen

    // 2 ---- Вычисление точки B
    Point B(
        D[0] + rotation_[0]*(screen_size_[0]/2-pixel_size_/2),
        D[1] + rotation_[1]*(screen_size_[0]/2-pixel_size_/2),
        D[2] + rotation_[2]*(screen_size_[0]/2-pixel_size_/2)
    ); 
    
    // 3 ---- Вычисление ортогонального вектора [b,n]
    std::vector<double> tau = {
        rotation_[1]*direction_of_view_[2]-rotation_[2]*direction_of_view_[1],
        rotation_[2]*direction_of_view_[0]-rotation_[0]*direction_of_view_[2],
        rotation_[0]*direction_of_view_[1]-rotation_[1]*direction_of_view_[0]};
    // Тут вектор должен получиться единичным, но из-за погрешностей - хз

    // 4 ---- Вычисление точки p[0][0]
    Point start(
        B[0]+tau[0]*(screen_size_[1]/2 - pixel_size_/2),
        B[1]+tau[1]*(screen_size_[1]/2 - pixel_size_/2),
        B[2]+tau[2]*(screen_size_[1]/2 - pixel_size_/2)
    );

    // После получения отсчётной точки, начнём вычисление луче, которые будут 
    // проходить через центр пикселя и пересекать фигуру
    
    // 5 ---- Пройдёмся по каждому пикселю, чтобы получить 
    // самую ближнюю точку пересечения
    int count=0;
    for(unsigned int i=0; i<screen_psize_[0]; ++i){
        for(unsigned int j=0; j<screen_psize_[1]; ++j){
            count++;
            // Проход по пересечениям фигуры
            std::tuple<bool, double, double> interns;

            interns = figure->intersection(start, point_of_view_, this->light_);
            
            if(std::get<0>(interns)==1){
                pixel_[i][j] = figure->get_colour();

                if(std::get<1>(interns)>=0 && std::get<2>(interns) == 0){ 
                    for(int l=0; l<3; ++l){
                        pixel_[i][j][l] = pixel_[i][j][l]*std::get<1>(interns);
                    }
                }
                else if(std::get<0>(interns)==1 && std::get<2>(interns) == 1){ pixel_[i][j] = {255,255,255};}
                else{ pixel_[i][j] = {0,0,0}; }
            }else{ pixel_[i][j] = {119, 136, 153}; }
            

            // В конце обязательно сделаем переход к соседнему cправа пикселю
            if(j < screen_psize_[1]-1){
                for(int k=0; k<3; ++k){ start[k] += (-1)*tau[k]*pixel_size_; }
            }
        }

        // Переход на следующую строку
        if(i < screen_psize_[0]-1){
            for(int k=0; k<3; ++k){ 
                start[k] += tau[k]*pixel_size_*(screen_psize_[1]-1); 
                start[k] += (-1)*rotation_[k]*pixel_size_;
            }
        }
    }
    // 6 ---- Конвертация изображения в bmp
    convert_to_bmp();
}

void Kinescope::convert_to_bmp(){
    cimg_library::CImg<unsigned char> img(this->screen_psize_[1], this->screen_psize_[0],1,3);

    int pheight = this->screen_psize_[0], pwidth = this->screen_psize_[1];

    #pragma omp parallel for
    for(int i=0; i<pheight; ++i){

        #pragma omp parallel for
        for(int j=0; j<pwidth; ++j){
            unsigned char color[3] = {this->pixel_[i][j][0], this->pixel_[i][j][1], this->pixel_[i][j][2]};
            img.draw_rectangle(j , i, (j+1), (i+1), color);
        }
    }

    img.save("Image.bmp");
    img.display();
}
//------------------------------------