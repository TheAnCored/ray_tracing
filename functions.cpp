#include "header.h"

Kinescope reading_scene(std::string& filename){

    std::ifstream filestream(filename);

    std::string str;

    //Kinescope kin;

    // data
    Point cam(0.,0.,0.);
    std::vector<double> normal(3, 0.);
    std::vector<double> rot(3, 0.);
    double dist=0.;
    double limit=0.;
    double alpha=0.;
    int pwidth=0;
    int pheight=0;
    Point light(0.,0.,0.);

    // Поиск параметров сцены по файлу
    while(getline(filestream, str)){

        std::string type;
        std::stringstream stream;

        stream<<str;
        stream>>type;
        
        // Пропуск комментариев в файле
        if(type[0] == '/' && type[1] == '/'){ 
            continue; 
        }

        // Нахождение сцены
        if( type == "SCENE" ){
           
            // Считывание параметров сцены
            while(getline(filestream, str))
            {
                stream.clear();
                type.clear();

                stream<<str;
                stream>>type;

                if(type[0] == '/' && type[1] == '/'){ continue; }

                if( type == "cam" ){
                    //Point cam(0.,0.,0.);
                    
                    for(int i=0; i<3; ++i){
                        stream >> cam[i]; 
                    }

                    //kin.set_camera(cam);
                }

                else if( type == "normal"){
                    //std::vector<double> normal(3, 0.);

                    for(int i=0; i<3; ++i){
                        stream >> normal[i]; 
                    }

                    //kin.set_normal(normal);
                }

                else if( type == "up"){
                    //std::vector<double> rot(3, 0.);

                    for(int i=0; i<3; ++i){
                        stream >> rot[i]; 
                    }

                    //kin.set_rotation(rot);
                }

                else if( type == "screen" ){
                    //double dist;

                    stream >> dist; 

                    //kin.set_screen_distance(dist);
                }

                else if( type == "limit" ){
                    //double limit;

                    stream >> limit; 

                    //kin.set_limit(limit);
                }

                else if( type == "alpha" ){
                    //double alpha;

                    stream >> alpha; 

                    //kin.set_angle_of_view(alpha);
                }

                else if( type == "width"){
                    //int pwidth;

                    stream >> pwidth; 

                    //kin.set_pwidth(pwidth);
                }

                else if( type == "height"){
                    //int pheight;

                    stream >> pheight; 

                    //kin.set_pheight(pheight);
                }

                else if( type == "light"){
                    //Point light(0.,0.,0.);
                    
                    for(int i=0; i<3; ++i){
                        stream >> light[i]; 
                    }

                    //kin.set_light(light);
                }
                else if( type == "END_SCENE") break;
            }
            //kin.setup();
            
            break;
        }
    }

    Kinescope kin(cam, pheight, pwidth, dist, alpha, limit, normal, rot,light);

    return kin;
}

std::vector<std::shared_ptr<Figure>> reading_figures(std::string& filename){
    std::ifstream filestream(filename);

    std::string str;

    std::string type;
    std::stringstream stream;

    std::vector<std::shared_ptr<Figure>> figures;

    // Поиск параметров сцены по файлу
    while(getline(filestream, str)){
        std::string type;
        std::stringstream stream;

        stream<<str;
        stream>>type;
        
        // Пропуск комментариев в файле
        if(type[0] == '/' && type[1] == '/'){ continue; }

        // Нахождение сцены
        if( type == "FIGURES" ){
            
            // Считывание фигур
            while(getline(filestream, str))
            {
                stream.clear();
                type.clear();

                stream<<str;
                stream>>type;

                if(type[0] == '/' && type[1] == '/'){ continue; }

                if( type == "sphere" ){
                    double radius; 
                    Point center(0., 0., 0.);
                    stream >> radius;

                    for(int i=0; i<3; ++i){ stream>> center[i];}

                    std::shared_ptr<Sphere> tmp = std::make_shared<Sphere>(radius, center);

                    figures.push_back(tmp);
                }
                else if( type == "cuboid" ){
                    Point a,b;

                    for(int i=0; i<3; ++i){
                        stream>>a[i];
                    }
                    for(int i=0; i<3; ++i){
                        stream>>b[i];
                    }

                    std::shared_ptr<Cuboid> tmp = std::make_shared<Cuboid>(a, b); 
                    
                    figures.push_back(tmp); 
                }
                else if( type == "tetr" ){
                    Point a,b,c,d;

                    for(int i=0; i<3; ++i){
                        stream >> a[i];
                    }
                    for(int i=0; i<3; ++i){
                        stream >> b[i];
                    }
                    for(int i=0; i<3; ++i){
                        stream >> c[i];
                    }
                    for(int i=0; i<3; ++i){
                        stream >> d[i];
                    }

                    std::shared_ptr<Tetr> tmp = std::make_shared<Tetr>(a, b, c, d);
                    figures.push_back(tmp); 
                }
                else if( type == "END_FIGURES") break;
            }

            break;
        }
    }

    return figures;
}