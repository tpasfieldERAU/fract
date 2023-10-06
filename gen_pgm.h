//
// Created by TJ on 10/05/2023.
//

#ifndef FRACT_GEN_PGM_H
#define FRACT_GEN_PGM_H

#endif //FRACT_GEN_PGM_H

#include <stdio.h>
#include <math.h>

void gen_pgm_binary(
    char * name,
    char * com,
    unsigned int x_resolution,
    unsigned int y_resolution,
    const unsigned int *data
);

void gen_pgm_ascii(
    char * name,
    char * com,
    unsigned int x_resolution,
    unsigned int y_resolution,
    const unsigned int *data
);