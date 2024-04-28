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
    double dot_product=0.0f;

    for(int i=0; i<3; ++i){
        dot_product += first[i]*second[i];
    }

    return dot_product;
}

std::vector<double> cross_product(std::vector<double> a, std::vector<double> b){
    std::vector<double> norm = { a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]};
    double module = sqrt(dot_product(norm, norm));

    for(int i=0; i<3; ++i){ 
        norm[i] /= module;
    }

    return norm;
}

std::vector<unsigned char> Figure::get_colour(){ return colour_;}