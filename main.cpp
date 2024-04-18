#include "header.h"
#include "autotests.h"

int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    Point center(3,12,12,-10);
    Sphere sph(center,{254,12,123});
    Cuboid cube;


    return 0;
}