#include "Disp.h"

//------Constructors-----------------------------
Disp::Disp(){
    this->screen_psize_[0] = 0;
    this->screen_psize_[1] = 0;

    pixel_size_ = 0.;

    this->screen_size_[0] = 0.;
    this->screen_size_[1] = 0.;

    this->direction_of_view_ = {0,0,0};
    this->rotation_ = {0,0,0};
}

Disp::Disp(uint pheight, uint pwidth){
    this->screen_psize_[0] = pheight;
    this->screen_psize_[1] = pwidth;

    pixel_size_ = 0.;

    this->screen_size_[0] = 0.;
    this->screen_size_[1] = 0.;

    this->direction_of_view_ = {0,0,0};
    this->rotation_ = {0,0,0};
}

Disp::Disp(uint pheight, uint pwidth, double distance, double angle){
    this->screen_psize_[0] = pheight;
    this->screen_psize_[1] = pwidth;

    this->direction_of_view_ = {0,0,0};
    this->rotation_ = {0,0,0};

    this->setup(distance, angle);
}

Disp::Disp(uint pheight, uint pwidth, double distance, double angle, vect norm, vect rot){
    this->screen_psize_[0] = pheight;
    this->screen_psize_[1] = pwidth;

    // Normalizing vectors
    double vector_eucl_norm = sqrt(pow(norm[0],2)+pow(norm[1],2)+pow(norm[2],2));
    for(int i=0; i<3; ++i){ 
        norm[i] /= vector_eucl_norm; 
    }

    for(int i=0; i<3; ++i){ 
        rot[i] /= sqrt(pow(rot[0],2)+pow(rot[1],2)+pow(rot[2],2)); 
    }
    //---
    
    this->direction_of_view_ = norm;
    this->rotation_ = rot;

    this->setup(distance, angle);
}
//------------------------------------

//-----Methods------------------------
int Disp::get_pheight(){ return this->screen_psize_[0]; }
int Disp::get_pwidth(){ return this->screen_psize_[1]; }

double Disp::get_height(){ return this->screen_size_[0]; }
double Disp::get_width(){ return this->screen_size_[1]; }

void Disp::set_pheight(uint height){ this->screen_size_[0] = height; }
void Disp::set_pwidth(uint width){ this->screen_size_[1] = width; }

void Disp::set_height(double height){ this->screen_size_[0] = height; }
void Disp::set_width(double width){ this->screen_size_[1] = width; }

void Disp::setup(double distance, double angle){
    if(this->screen_psize_[0]==0 || this->screen_psize_[1]==0){ std::cout<<"GIVEN ZERO\n---BREAK---\n\n"; return; }

    this->screen_size_[0] = 2*tan(RAD(angle/2))*distance;
    this->pixel_size_ = this->screen_size_[0]/this->screen_psize_[0];
    this->screen_size_[1] = this->pixel_size_*this->screen_psize_[1];

    // Выделение памяти для массива пикселей
    this->pixel_ = pixels(this->screen_psize_[0]);
    for(unsigned int i=0; i<this->screen_psize_[0]; ++i){
        this->pixel_[i] = std::vector<std::vector<unsigned char>>(this->screen_psize_[1]);
        
        for(unsigned int j=0; j<this->screen_psize_[1]; ++j){
            this->pixel_[i][j] = std::vector<unsigned char>(3);
        }
    }
}

void Disp::setup(uint pheight, uint pwidth, double distance, double angle){
    this->screen_psize_[0] = pheight; this->screen_psize_[1] = pwidth;
    
    if(this->screen_psize_[0]==0 || this->screen_psize_[1]==0){ std::cout<<"GIVEN ZERO\n---BREAK---\n\n"; return; }

    this->screen_size_[0] = 2*tan(RAD(angle/2))*distance;
    this->pixel_size_ = this->screen_size_[0]/this->screen_psize_[0];
    this->screen_size_[1] = pixel_size_*this->screen_psize_[1];

    this->pixel_ = pixels(this->screen_psize_[0]);
    for(unsigned int i=0; i<this->screen_psize_[0]; ++i){
        this->pixel_[i] = std::vector<std::vector<unsigned char>>(this->screen_psize_[1]);
        
        for(unsigned int j=0; j<this->screen_psize_[1]; ++j){
            this->pixel_[i][j] = std::vector<unsigned char>(3);
        }
    }
}