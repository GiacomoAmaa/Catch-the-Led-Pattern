#include "support.h"

int[] diffScaler {256, 512, 768, 1024};
int diff = 1;
int potVal = 0;

set_diff(int newVal){
    if(potVal != newVal){
        int i ;
        for (i = 0; i < 4; i++){
            if(newVal < diffScaler[i]){
                return i + 1;  
            }
        }
        potVal = newVal;
    }
    return diff;
}
