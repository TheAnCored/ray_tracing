#include "Figure.h"

//-----Constructors------------------------------
Figure::Figure(){
    std::get<0>(this->colour) = 255;
    std::get<1>(this->colour) = 255;
    std::get<2>(this->colour) = 255;
}

Figure::Figure(unsigned char R, unsigned char G, unsigned char B){
    std::get<0>(this->colour) = R;
    std::get<1>(this->colour) = G;
    std::get<2>(this->colour) = B;
}
//-----------------------------------------------
//------Methods----------------------------------

//------COLOURS---------
void Figure::set_colour(unsigned char R, unsigned char G, unsigned char B){
    this->colour = {R, G, B};
}
void Figure::set_r(unsigned char R){
    std::get<0>(this->colour) = R;
}   
void Figure::set_g(unsigned char G){
    std::get<1>(this->colour) = G;
}   
void Figure::set_b(unsigned char B){
    std::get<2>(this->colour) = B;
}   
//----------------------

double dot_product(std::vector<double> first, std::vector<double> second){
    double dot_product=0.;

    #pragma omp parallel for reduction(+: dot_product)
    for(int i=0; i<N; ++i){
        dot_product = dot_product+first[i]*second[i];
    }
    return dot_product;
}