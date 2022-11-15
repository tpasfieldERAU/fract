//
// Created by TJ on 11/13/2022.
//

#ifndef FRACT_COLOR_MAP_H
#define FRACT_COLOR_MAP_H

#endif //FRACT_COLOR_MAP_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "data_write.h"
#include "progress_bar.h"

void gen_color_ppm(
        char * name,
        char * com,
        unsigned int x_resolution,
        unsigned int y_resolution,
        const unsigned int *data_block_1,
        const unsigned int *data_block_2,
        const unsigned int *data_block_3
);

void color_map(
        unsigned int x_resolution,
        unsigned int y_resolution,
        unsigned int escape_limit);
