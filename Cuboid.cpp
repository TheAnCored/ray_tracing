#include "Cuboid.h"

//-----Constructors--------------------------
Cuboid::Cuboid():Figure(){

    this->vertexes = space(2);
    for(int i=0; i<2;++i){
        this->vertexes[i] = plane(2);
        for(int j=0; j<2; ++j){
            this->vertexes[i][j] = line(2);
        }
    }

    this->colour = {255,255,255};
}

Cuboid::Cuboid(Point nearest, Point farther):Figure(){
    
    this->vertexes = space(2);
    for(int i=0; i<2;++i){
        this->vertexes[i] = plane(2);
        for(int j=0; j<2; ++j){
            this->vertexes[i][j] = line(2);
        }
    }

    this->colour = {255,255,255};

    this->vertexes[0][0][0] = nearest;
    this->vertexes[1][1][1] = farther;

    this->calculate_vertexes();
}
//-------------------------------------------

//-----Methods-------------------------------
void Cuboid::calculate_vertexes(){
    double length=0., width=0.;

    std::vector<double> ox{1,0,0};
    std::vector<double> oy{0,1,0};

    std::vector<double> diagonal_vector(3,0.);
    for(int i=0; i<N; ++i){
       diagonal_vector[i] = this->vertexes[1][1][1][i] - this->vertexes[0][0][0][i];
    }

    length = dot_product(ox, diagonal_vector);
    width = dot_product(oy, diagonal_vector);

// Здесь постепенно по нумерации точек прибавляем по нужной координате: всего необходимо определить 
// шесть точек
    this->vertexes[0][0][1] = this->vertexes[0][0][0]; this->vertexes[0][0][1][0]+=length;
    this->vertexes[0][1][0] = this->vertexes[0][0][0]; this->vertexes[0][1][0][0]+=width;
    this->vertexes[0][1][1] = this->vertexes[0][0][0]; this->vertexes[0][1][1][0]+=(length+width);
    this->vertexes[1][0][0] = this->vertexes[1][1][1]; this->vertexes[1][0][0][0]-=(length+width);
    this->vertexes[1][0][1] = this->vertexes[1][1][1]; this->vertexes[1][0][1][0]-=width;
    this->vertexes[1][1][0] = this->vertexes[1][1][1]; this->vertexes[1][1][0][0]-=length;
}
//-------------------------------------------