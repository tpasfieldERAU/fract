//
// Created by TJ on 10/23/2022.
//

#include "data_write.h"

void data_write(
        const unsigned int *mapBuff,
        unsigned int *data,
        unsigned int i,
        unsigned int x_resolution
        ){
    unsigned int x, y;

    for (unsigned int j = 1; j < i; j++){
        x = mapBuff[2*j];
        y = mapBuff[2*j+1];
        data[x_resolution*y+x] += 1;
    }
}
