extern "C" {
    #include <tinyPTC/src/tinyptc.h>
}
#include <cstdint> // uint32_t
//#include <iostream>

//using namespace std;

//crear un array

int  width = 480;
int height = 272;
uint32_t screen[480 * 272];

int main(){

ptc_open("Juego",width,height);
while(true){
for(uint32_t i=0;i < (480*272);++i){
        screen[i]=0x00999999;
    }
    
    ptc_update(screen);
}
ptc_close();

//cout<< "my first program gamer " <<endl;
return 0;
}
