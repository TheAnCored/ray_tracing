#include "Figure.h"

//------ using points = std::vector<std::vector<std::vector<Point>>> -----

class Cuboid: protected Figure{
private:
    // Here are points is vertexes of rectangular cuboid
    space vertexes; 

public:
//-----Constructors--------------------------    
    Cuboid(); // Empty
    // Two opposite points of cuboid
    Cuboid(Point, Point);
//-------------------------------------------

//-----Methods-------------------------------
    // This is a method that allows you to find all the vertices of a cuboid by two opposite
    void calculate_vertexes();
//-------------------------------------------
};