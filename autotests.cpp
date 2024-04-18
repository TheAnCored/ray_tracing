#include "autotests.h"

int point_sum_test(){

    Point a(3,1,2,34);
    Point b(3,3,4,112);

    Point c = a+b;
    Point d; d = a+b;

    if(c[1]==6 && c[2]==146 && d[1]==6 && d[2]==146){ return 0; }

    return 1;
}

int point_sub_test(){

    Point a(3,1,2,34);
    Point b(3,3,4,112);

   Point c = a-b;
   Point d; d = a-b;

    if(c[1]==-2 && c[2]==-78 && d[1]==-2 && d[2]==-78){ return 0;}

    return 1;
}

int MainTest(){
    if( point_sum_test()==0 && point_sub_test()==0 ){ return 0; }
    return 1;
}