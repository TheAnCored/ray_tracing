#include "Point.h"


//-----Constructors------------------------------------

Point::Point(){ 
    this->point = std::make_unique<double[]>(N); 

    for(int i=0; i<N; ++i){ this->point[i]=0.; }
}


Point::Point(std::unique_ptr<double[]> coordinates){
    this->point = std::make_unique<double[]>(N);

    for(int i=0; i<N; ++i){ this->point[i] = coordinates[i]; }
}

Point::Point(std::shared_ptr<double[]> coordinates){
    this->point = std::make_unique<double[]>(N);

    for(int i=0; i<N; ++i){ this->point[i] = coordinates[i]; }
}

Point::Point(int index, ...){
    this->point = std::make_unique<double[]>(N);

    va_list args;
    
    // Initialize position of va_list
    va_start(args, index);

    for(int i=0; i<N; ++i){ this->point[i] = va_arg(args, int); }

    // End of using va_list
    va_end(args);
}

// Copy constructor
Point::Point(const Point& second){
    this->point = std::make_unique<double[]>(N);

    for(int i=0; i<N; ++i){ this->point[i] = second[i];}
}

// Move constructor
Point::Point(Point&& second){
    this->point = std::move(second.point);
}
//---------------------------------------------------

//------Operators------------------------------------
// []
double& Point::operator[](int index){ return this->point[index]; }
double& Point::operator[](int index) const { return this->point[index]; }

// +
Point Point::operator+(const Point& second)const{
    Point temp;
    for(int i=0; i<N; ++i){ temp[i] = this->point[i] + second[i]; }

    return temp;
}

// -
Point Point::operator-(const Point& second)const{
    Point temp;
    for(int i=0; i<N; ++i){ temp[i] = this->point[i] - second.point[i]; }

    return temp;
}

// = (with copy constructor)
Point& Point::operator=(const Point& second){
    for(int i=0; i<N; ++i){ this->point[i] = second[i];}
    
    return *this;
}

// = (with move constructor)
Point& Point::operator=(Point&& second){
    this->point = std::move(second.point);

    return *this;
}

//---------------------------------------------------

//-----Methods---------------------------------------
void Point::write(std::shared_ptr<double[]> temp){
    for(int i=0; i<N; ++i){
        this->point[i] = temp[i];
    }
}

void Point::write(std::unique_ptr<double[]> temp){
    this->point = std::move(temp);
}
//---------------------------------------------------