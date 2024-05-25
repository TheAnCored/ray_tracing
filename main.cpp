#include "header.h"

int main(){
    //---------Autotests---------
    if(MainTest()!=0){ return 1; }
    //---------------------------

    std::vector<std::shared_ptr<Figure>> figures;
    Kinescope kin;

    std::string filename = "data.txt";

    kin = reading_scene(filename);
    figures = reading_figures(filename);

    kin.get_image(figures);

    return 0;
}