//
// Created by TJ on 10/24/2022.
//

#ifndef FRACT_IMPORTANCE_MAP_H
#define FRACT_IMPORTANCE_MAP_H

#endif //FRACT_IMPORTANCE_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void write_im_map(
        const unsigned int *buffer,
        unsigned int *data,
        unsigned int i,
        unsigned int x_resolution,
        unsigned int x,
        unsigned int y,
        const unsigned int x_range[2],
        const unsigned int y_range[2]
);

void importance_map(
        unsigned int x_resolution,
        unsigned int y_resolution,
        unsigned int escape_limit,
        unsigned int *data
);
