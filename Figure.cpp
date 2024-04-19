#include "Figure.h"

//-----Constructors------------------------------
Figure::Figure(){
    std::get<0>(this->colour_) = 255;
    std::get<1>(this->colour_) = 255;
    std::get<2>(this->colour_) = 255;
}

Figure::Figure(unsigned int R, unsigned int G, unsigned int B){
    std::get<0>(this->colour_) = R;
    std::get<1>(this->colour_) = G;
    std::get<2>(this->colour_) = B;
}
//-----------------------------------------------
//------Methods----------------------------------

//------COLOURS---------
void Figure::set_colour(unsigned int R, unsigned int G, unsigned int B){
    this->colour_ = {R, G, B};
}
void Figure::set_r(unsigned int R){
    std::get<0>(this->colour_) = R;
}   
void Figure::set_g(unsigned int G){
    std::get<1>(this->colour_) = G;
}   
void Figure::set_b(unsigned int B){
    std::get<2>(this->colour_) = B;
}   
//----------------------

double dot_product(std::vector<double> first, std::vector<double> second){
    double dot_product=0.;

    //#pragma omp parallel for reduction(+: dot_product)
    for(int i=0; i<3; ++i){
        dot_product = dot_product+first[i]*second[i];
    }
    return dot_product;
}