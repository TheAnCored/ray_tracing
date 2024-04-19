#include "Screen.h"

// Constructors
Screen::Screen(){
    this->screen_psize[0] = 0;
    this->screen_psize[1] = 0;

    pixel_size = 0.;

    this->screen_size[0] = 0.;
    this->screen_size[1] = 0.;

    this->direction_of_view = {0,0,0};
    this->rotation = {0,0,0};
}

Screen::Screen(uint pheight, uint pwidth){
    this->screen_psize[0] = pheight;
    this->screen_psize[1] = pwidth;

    pixel_size = 0.;

    this->screen_size[0] = 0.;
    this->screen_size[1] = 0.;

    this->direction_of_view = {0,0,0};
    this->rotation = {0,0,0};
}

Screen::Screen(uint pheight, uint pwidth, double distance, double angle){
    this->screen_psize[0] = pheight;
    this->screen_psize[1] = pwidth;

    this->direction_of_view = {0,0,0};
    this->rotation = {0,0,0};

    this->setup(distance, angle);
}

Screen::Screen(uint pheight, uint pwidth, double distance, double angle, vect norm, vect rot){
    this->screen_psize[0] = pheight;
    this->screen_psize[1] = pwidth;

    this->direction_of_view = norm;
    this->rotation = rot;

    this->setup(distance, angle);
}
//=------------=

//-----Methods-------
int Screen::get_pheight(){ return this->screen_psize[0]; }
int Screen::get_pwidth(){ return this->screen_psize[1]; }

double Screen::get_height(){ return this->screen_size[0]; }
double Screen::get_width(){ return this->screen_size[1]; }

void Screen::set_pheight(uint height){ this->screen_size[0] = height; }
void Screen::set_pwidth(uint width){ this->screen_size[1] = width; }

void Screen::set_height(double height){ this->screen_size[0] = height; }
void Screen::set_width(double width){ this->screen_size[1] = width; }

void Screen::setup(double distance, double angle){
    if(this->screen_psize[0]==0 || this->screen_psize[1]==0){ std::cout<<"GIVEN ZERO\n---BREAK---\n\n"; return; }

    this->screen_size[0] = 2*tan(RAD(angle/2))*distance;
    this->pixel_size = this->screen_size[0]/this->screen_psize[0];
    this->screen_size[1] = pixel_size*this->screen_psize[1];
}

void Screen::setup(uint pheight, uint pwidth, double distance, double angle){
    this->screen_psize[0] = pheight; this->screen_psize[1] = pwidth;
    
    if(this->screen_psize[0]==0 || this->screen_psize[1]==0){ std::cout<<"GIVEN ZERO\n---BREAK---\n\n"; return; }

    this->screen_size[0] = 2*tan(RAD(angle/2))*distance;
    this->pixel_size = this->screen_size[0]/this->screen_psize[0];
    this->screen_size[1] = pixel_size*this->screen_psize[1];
}