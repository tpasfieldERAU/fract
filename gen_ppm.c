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

    static unsigned char color[3];
    FILE * image;
    image = fopen(name, "wb");
    fprintf(image, "P6\n%s\n%d\n%d\n%d\n", com, x_resolution, y_resolution, 255);
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            unsigned char val = (unsigned char) rint(((double) data[x_resolution * y + x] / (double) max) * 255);
            color[0] = val;
            color[1] = val;
            color[2] = val;
            fwrite(color, 1, 3, image);
        }
    }
    fclose(image);
}
