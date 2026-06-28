extern "C" {
    #include "tinyPTC/tinyptc.h"
}

//#include <iostream>

//using namespace std;

int main(){

ptc_open("Juego",640,320);
ptc_close();
//cout<< "my first program gamer " <<endl;
return 0;
}
