#include "Figure.h"

//-----Constructors------------------------------
Figure::Figure(){
    this->colour_ = {255,255,255};
}

Figure::Figure(unsigned char R, unsigned char G, unsigned char B){
    this->colour_ = {R,G,B};
}
//-----------------------------------------------
//------Methods----------------------------------

//------COLOURS---------
void Figure::set_colour(unsigned char R, unsigned char G, unsigned char B){ this->colour_ = {R, G, B}; }
void Figure::set_r(unsigned char R){ this->colour_[0] = R; }   
void Figure::set_g(unsigned char G){ this->colour_[1] = G; }   
void Figure::set_b(unsigned char B){ this->colour_[2] = B; }   
//----------------------

double dot_product(std::vector<double> first, std::vector<double> second){
    double dot_product=0.;

    //#pragma omp parallel for reduction(+: dot_product)
    for(unsigned int i=0; i<3; ++i){
        dot_product = dot_product+first[i]*second[i];
    }
    return dot_product;
}