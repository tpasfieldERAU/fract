//
// Created by TJ on 10/23/2022.
//

#include "gen_ppm.h"

void gen_ppm(
        char * name,
        char * com,
        unsigned int x_resolution,
        unsigned int y_resolution,
        const unsigned int *data
){
    unsigned int max = 0;
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            if (data[x_resolution * y + x] > max) {
                max = data[x_resolution * y + x];
            }
        }
    }


    /* TEMPORARILY CHANGED TO USE SINUSOIDAL SCALE. */

    long double val;

    static unsigned char color[3];
    FILE * image;
    image = fopen(name, "wb");
    fprintf(image, "P6\n%s\n%d\n%d\n%d\n", com, x_resolution, y_resolution, 255);
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            val = data[x_resolution * y + x] / max;
            color[0] = val <= 0.5 ? sin(2.0f*M_PI*val)*255 : 255;
            color[1] = val <= 0.5 ? sin(2.0f*M_PI*val)*255 : 255;
            color[2] = val <= 0.5 ? sin(2.0f*M_PI*val)*255 : 255;
            fwrite(color, 1, 3, image);
        }


        /* TEMP CHANGE FOR SINUSOIDAL SCALE
        for (unsigned int x = 0; x < x_resolution; x++){
            color[0] = ((double) data[x_resolution * y + x] / (double) max) * 255;
            color[1] = ((double) data[x_resolution * y + x] / (double) max) * 255;
            color[2] = ((double) data[x_resolution * y + x] / (double) max) * 255;
            fwrite(color, 1, 3, image);
        }
        */
    }
    fclose(image);
}
