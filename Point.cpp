#include "Point.h"


//-----Constructors------------------------------------

Point::Point(){ 
    this->point_ = std::make_unique<double[]>(3); 

    for(long long unsigned int i=0; i<3; ++i){ this->point_[i]=0.; }
}


Point::Point(std::unique_ptr<double[]> coordinates){
    this->point_ = std::make_unique<double[]>(3);

    for(int i=0; i<3; ++i){ this->point_[i] = coordinates[i]; }
}

Point::Point(std::shared_ptr<double[]> coordinates){
    this->point_ = std::make_unique<double[]>(3);

    for(int i=0; i<3; ++i){ this->point_[i] = coordinates[i]; }
}

Point::Point(double c1, double c2, double c3){
    this->point_ = std::make_unique<double[]>(3);
    
    this->point_[0] = c1; this->point_[1] = c2; this->point_[2] = c3; 
} 

// Copy constructor
Point::Point(const Point& second){
    this->point_ = std::make_unique<double[]>(3);

    for(int i=0; i<3; ++i){ this->point_[i] = second[i];}
}

// Move constructor
Point::Point(Point&& second){
    this->point_ = std::move(second.point_);
}
//---------------------------------------------------

//------Operators------------------------------------
// []
double& Point::operator[](int index){ return this->point_[index]; }
double& Point::operator[](int index) const { return this->point_[index]; }

// +
Point Point::operator+(const Point& second)const{
    Point temp;
    for(int i=0; i<3; ++i){ temp[i] = this->point_[i] + second[i]; }

    return temp;
}

// -
Point Point::operator-(const Point& second)const{
    Point temp;
    for(int i=0; i<3; ++i){ temp[i] = this->point_[i] - second.point_[i]; }

    return temp;
}

// = (with copy constructor)
Point& Point::operator=(const Point& second){
    for(int i=0; i<3; ++i){ this->point_[i] = second[i];}
    
    return *this;
}

// = (with move constructor)
Point& Point::operator=(Point&& second){
    this->point_ = std::move(second.point_);

    return *this;
}

//---------------------------------------------------

//-----Methods---------------------------------------
void Point::write(std::shared_ptr<double[]> temp){
    for(int i=0; i<3; ++i){
        this->point_[i] = temp[i];
    }
}

void Point::write(std::unique_ptr<double[]> temp){
    this->point_ = std::move(temp);
}
//---------------------------------------------------