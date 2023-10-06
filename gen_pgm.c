//
// Created by TJ on 10/05/2023.
//

#include "gen_pgm.h"

void gen_pgm_binary(
    char * name,
    char * com,
    unsigned int x_resolution,
    unsigned int y_resolution,
    const unsigned int *data
){
    unsigned int max = 0;
    for (unsigned int y = 0; y < y_resolution; ++y){
        for (unsigned int x = 0; x < x_resolution; ++x){
            if (data[x_resolution * y + x] > max) {
                max = data[x_resolution * y + x];
            }
        }
    }

    unsigned int val[1];

    FILE * image;
    image = fopen(name, "wb");
    fprintf(image, "P5 %d %d %d\n", x_resolution, y_resolution, max);
    for (unsigned int y = 0; y < y_resolution; ++y){
        for (unsigned int x = 0; x < x_resolution; ++x){
            val[0] = data[x_resolution * y + x];
            fwrite(val, 1, 1, image);
        }
    }
    fclose(image);
}

void gen_pgm_ascii(
    char * name,
    char * com,
    unsigned int x_resolution,
    unsigned int y_resolution,
    const unsigned int *data
){
    unsigned int max = 0;
    for (unsigned int y = 0; y < y_resolution; ++y){
        for (unsigned int x = 0; x < x_resolution; ++x){
            if (data[x_resolution * y + x] > max) {
                max = data[x_resolution * y + x];
            }
        }
    }

    unsigned int val[1];

    FILE * image;
    image = fopen(name, "wb");
    fprintf(image, "P2 %d %d %d\n", x_resolution, y_resolution, max);
    for (unsigned int y = 0; y < y_resolution; ++y){
        for (unsigned int x = 0; x < x_resolution; ++x){
            fprintf(image, "%d ", data[x_resolution * y + x]);
        }
    }
    fclose(image);
}