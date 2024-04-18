#include "header.h"


int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    Point center;
    Sphere sph(center,{254,12,123});
    Cuboid cube;

    return 0;
}