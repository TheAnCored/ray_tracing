#include "Tetrahedron.h"

Tetr::Tetr(){ this->colour_ = {255,255,255}; }

Tetr::Tetr(Point& a,Point& b,Point& c, Point& d){

    std::vector<double> vect1 = {b[0]-a[0], b[1]-a[1], b[2]-a[2]};
    std::vector<double> vect2 = {c[0]-a[0], c[1]-a[1], c[2]-a[2]};

    std::vector<double> normal = cross_product(vect1,vect2);

    if(normal[0]*(d[0]-a[0])+normal[1]*(d[1]-a[1])+normal[2]*(d[2]-a[2])>0){
        Point tmp = b; b = c; c = tmp;
    }
    // 1я грань (ABC)
    vertexes[0][0] = std::make_shared<Point>(a); //a
    vertexes[0][1] = std::make_shared<Point>(b); //b
    vertexes[0][2] = std::make_shared<Point>(c); //c

    // 2я грань (ADB)
    vertexes[1][0] = vertexes[0][0]; //a
    vertexes[1][1] = std::make_shared<Point>(d); //d
    vertexes[1][2] = vertexes[0][1]; //b

    // 3я грань (AСD)
    vertexes[2][0] = vertexes[0][0]; //a
    vertexes[2][1] = vertexes[0][2]; //c 
    vertexes[2][2] = vertexes[1][1]; //d

    // 4я грань (BDC)
    vertexes[3][0] = vertexes[0][1]; //b
    vertexes[3][1] = vertexes[1][1]; //d
    vertexes[3][2] = vertexes[0][2]; //c

    this->colour_ = {255,255,255};
}

//--------------------------------------

//------Methods-------------------------
std::tuple<bool, double, bool, double> Tetr::intersection(Point& P, Point& C, Point& L){
   std::tuple<bool, double, bool, double> parameters = {false, 1, false, 0.};

    // Вычисление точки пересечения
    Point M;

    double t=0.; // Параметр пересечения
    double temp_t = 0.; // Временный параметр пересечения, который будем считать

    std::vector<std::vector<double>> Normal(4);

   
    for(int i=0; i<4; ++i){
        std::vector<double> AB = {(*vertexes[i][1])[0]-(*vertexes[i][0])[0], (*vertexes[i][1])[1]-(*vertexes[i][0])[1], (*vertexes[i][1])[2]-(*vertexes[i][0])[2]};
        std::vector<double> AC = {(*vertexes[i][2])[0]-(*vertexes[i][0])[0], (*vertexes[i][2])[1]-(*vertexes[i][0])[1], (*vertexes[i][2])[2]-(*vertexes[i][0])[2]};

        Normal[i] = {AB[1]*AC[2]-AB[2]*AC[1], AB[2]*AC[0]-AB[0]*AC[2], AB[0]*AC[1]-AB[1]*AC[0]};
    }

    std::vector<double> normal;
    std::vector<double> normal_tmp;
    
    for(int i=0, k=0; i<4; ++i){
    
        normal_tmp = Normal[i];

        if(normal_tmp[0]*(C[0]-P[0])+normal_tmp[1]*(C[1]-P[1])+normal_tmp[2]*(C[2]-P[2]) == 0.){ continue; } // Условие параллельности

        temp_t = (normal_tmp[0]*(P[0]-(*vertexes[i][0])[0])+normal_tmp[1]*(P[1]-(*vertexes[i][0])[1])+normal_tmp[2]*(P[2]-(*vertexes[i][0])[2]))/(normal_tmp[0]*(C[0]-P[0])+normal_tmp[1]*(C[1]-P[1])+normal_tmp[2]*(C[2]-P[2]));
        if(k>0 && temp_t>t){
            continue;   
        }

        if(temp_t < 0.){ continue; }
        else if( temp_t == 0.){
            t = temp_t;
            M = P;
            std::get<0>(parameters) = true;
            continue;
        }

        Point m;

        // Вычислим точку пересечения
        for(int j=0; j<3; ++j){
            m[j] = P[j] +temp_t*(P[j]-C[j]);
        }

        // Теперь определим положение точки относительно грани тетраэдра
        std::vector<double> norm1(3,0.);
        std::vector<double> norm2(3,0.);
        std::vector<double> norm3(3,0.);

        bool tmp=false;

        // Тут расчитаем все нормали
        for(int j=0, l=0; j<3; ++j){
            if(j==2){ l = 0;}// Параметр для возврата в точку 0
            else{ l=j+1; }

            std::vector<double> side = {(*vertexes[i][l])[0]-(*vertexes[i][j])[0],(*vertexes[i][l])[1]-(*vertexes[i][j])[1],(*vertexes[i][l])[2]-(*vertexes[i][j])[2]};
            std::vector<double> to_point = {m[0] - (*vertexes[i][j])[0], m[1] - (*vertexes[i][j])[1], m[2] - (*vertexes[i][j])[2]};

            if(j==0){ norm1 = cross_product(side, to_point);}
            else if(j==1){ norm2 = cross_product(side, to_point); }
            else{ norm3 = cross_product(side, to_point); }
        }
        
        // Теперь покоординатно сравним их
        for(int ct=0; ct<3; ++ct){
            if(std::abs(norm1[ct]-norm2[ct])<=std::numeric_limits<float>::epsilon() &&
               std::abs(norm2[ct]-norm3[ct])<=std::numeric_limits<float>::epsilon() &&
               std::abs(norm1[ct]-norm3[ct])<=std::numeric_limits<float>::epsilon()
            ){ tmp = true; }
            else{ 
                tmp = false;
                break;
            }
        }


        if(tmp == true){
            ++k;
        
            t = temp_t;
            M = m;
            std::get<0>(parameters) = true;
            std::get<3>(parameters) = t;

            normal = normal_tmp;
        }   
    }
    
    if(std::get<0>(parameters)==true){
        std::vector<double> light = {L[0]-M[0], L[1]-M[1], L[2]-M[2]};

        double module_light = sqrt(dot_product(light, light));
        double module_norm = sqrt(dot_product(normal,normal));

        for(int i=0; i<3; ++i){
            light[i] /= module_light;
            normal[i] /= module_norm;
        }

        std::get<1>(parameters) = dot_product(light, normal);
    }

    return parameters; 
}