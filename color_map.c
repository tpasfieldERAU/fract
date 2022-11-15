//
// Created by TJ on 11/13/2022.
//
// Make it track escapes better
// https://en.wikipedia.org/wiki/Histogram_equalization
#include "color_map.h"

void gen_color_ppm(
        char * name,
        char * com,
        unsigned int x_resolution,
        unsigned int y_resolution,
        const unsigned int *data_block_1,
        const unsigned int *data_block_2,
        const unsigned int *data_block_3
){
    unsigned int max_1 = 0;
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            if (data_block_1[x_resolution * y + x] > max_1) {
                max_1 = data_block_1[x_resolution * y + x];
            }
        }
    }

    unsigned int max_2 = 0;
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            if (data_block_2[x_resolution * y + x] > max_2) {
                max_2 = data_block_2[x_resolution * y + x];
            }
        }
    }

    unsigned int max_3 = 0;
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            if (data_block_3[x_resolution * y + x] > max_3) {
                max_3 = data_block_3[x_resolution * y + x];
            }
        }
    }

    static unsigned char color[3];
    FILE * image;
    image = fopen(name, "wb");
    fprintf(image, "P6\n%s\n%d\n%d\n%d\n", com, x_resolution, y_resolution, 255);
    for (unsigned int y = 0; y < y_resolution; y++){
        for (unsigned int x = 0; x < x_resolution; x++){
            unsigned char val_1 = (unsigned char) rint(sqrt((double) data_block_1[x_resolution * y + x] / (double) max_1) * 255);
            unsigned char val_2 = (unsigned char) rint(sqrt((double) data_block_2[x_resolution * y + x] / (double) max_2) * 255);
            unsigned char val_3 = (unsigned char) rint(sqrt((double) data_block_3[x_resolution * y + x] / (double) max_3) * 255);

            color[0] = val_1;
            color[1] = val_2;
            color[2] = val_3;
            fwrite(color, 1, 3, image);
        }
    }
    fclose(image);
}

void color_map(
        unsigned int x_resolution,
        unsigned int y_resolution,
        unsigned int escape_limit)
{
    // Red, Green, and Blue Segments
    unsigned int *data_block_1;
    data_block_1 = (unsigned int *) calloc(x_resolution * y_resolution, sizeof(unsigned int));
    unsigned int *data_block_2;
    data_block_2 = (unsigned int *) calloc(x_resolution * y_resolution, sizeof(unsigned int));
    unsigned int *data_block_3;
    data_block_3 = (unsigned int *) calloc(x_resolution * y_resolution, sizeof(unsigned int));

    const double half_x = x_resolution / 2.0, half_y = y_resolution / 2.0, scalar = 4.0 / y_resolution;

    unsigned int x, y;
    unsigned int conv_test_var = 0;
    double a_old = 0.0, b_old = 0.0;

    double x0, y0;
    double a, b;
    unsigned int i;
    double a2, b2;

    unsigned int scDiv2 = 16;
    unsigned int scDiv3 = 128;

    unsigned int * mapBuff_1;
    //mapBuff_1 = malloc(sizeof *mapBuff_1 * 2 * escape_limit);
    mapBuff_1 = calloc(2*escape_limit, sizeof *mapBuff_1);
    unsigned int * mapBuff_2;
    //mapBuff_2 = malloc(sizeof *mapBuff_2 * 2 * escape_limit / scDiv2);
    mapBuff_2 = calloc(2*escape_limit/scDiv2, sizeof *mapBuff_2);

    unsigned int * mapBuff_3;
    //mapBuff_3 = malloc(sizeof *mapBuff_3 * 2 * escape_limit / scDiv3);
    mapBuff_3 = calloc(2*escape_limit/scDiv3, sizeof *mapBuff_3);

    for (y = 0; y < y_resolution; y++) {
        if (y % (int) (y_resolution / 64) == 0) progress_bar_update((double) y / (double) y_resolution);
        for (x = 0; x < x_resolution; x++) {
            x0 = (x - half_x) * scalar;
            y0 = (y - half_y) * scalar;

            a  = 0.0;
            b  = 0.0;
            i  = 0;
            a2 = 0.0;
            b2 = 0.0;

            if (a2 + b2 > 4.0) continue;
            // BULB CONSTANT x^2-0.5x+0.0625+y^2
            double bc = x0*x0 - 0.5*x0 + 0.0625 + y0*y0;
            // Cardioid Check
            if (bc * (bc + (x0 - 0.25)) <= 0.25 * (y0 * y0)) continue;

            // Period 2 Bulb Check
            if (x*x + 2*x + 1 + y*y <= 0.0625) continue;

            while(1) {
                if(i == escape_limit) break;

                b = (a+a)*b + y0;
                a = a2-b2 + x0;

                if (a == a_old && b == b_old){
                    i = escape_limit;
                    break;
                }

                conv_test_var++;
                if(conv_test_var > 20) {
                    conv_test_var = 0;
                    a_old = a;
                    b_old = b;
                }

                a2 = a * a;
                b2 = b * b;

                if(a2 + b2 > 4.0) break;
                mapBuff_1[2*i]   = (unsigned int) ( a / scalar + half_x);
                mapBuff_1[2*i+1] = (unsigned int) ( b / scalar + half_y);

                if(i < escape_limit / scDiv2) {
                    mapBuff_2[2*i]   = (unsigned int) ( a / scalar + half_x);
                    mapBuff_2[2*i+1] = (unsigned int) ( b / scalar + half_y);
                }

                if(i < escape_limit / scDiv3) {
                    mapBuff_3[2*i]   = (unsigned int) ( a / scalar + half_x);
                    mapBuff_3[2*i+1] = (unsigned int) ( b / scalar + half_y);
                }
                i++;
            }
            if(i == escape_limit) continue;
            data_write(mapBuff_1, data_block_1, i, x_resolution);
            if(i > (escape_limit / scDiv2)) continue;
            data_write(mapBuff_2, data_block_2, i, x_resolution);
            if(i > (escape_limit / scDiv3)) continue;
            data_write(mapBuff_3, data_block_3, i, x_resolution);
        }
    }
    gen_color_ppm("color.ppm", "# ", x_resolution, y_resolution-1, data_block_1, data_block_2, data_block_3);

    free(mapBuff_1);
    free(data_block_1);
    free(data_block_2);
    free(data_block_3);
}