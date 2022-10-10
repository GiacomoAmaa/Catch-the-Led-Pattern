#include "support.h"

int[] diffScaler {256, 512, 768, 1024};
int diff = 1;

set_difficulty(int newVal){
    int i ;
    for (i = 0; i < 4; i++){
        if(newVal < diffScaler[i]){
            diff = i + 1;
            break;
        }
    }
}

get_difficulty(){
    return diff;
}