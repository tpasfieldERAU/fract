//
// Created by TJ on 10/23/2022.
//

#include "freq_map.h"

void freq_map(
        unsigned int x_resolution,
        unsigned int y_resolution,
        unsigned int escape_limit,
        unsigned int * data
        ){
    const double half_x = x_resolution / 2.0, half_y = y_resolution / 2.0, scalar = 4.0 / y_resolution;
    unsigned int x, y;
    int conv_test_var = 0;
    double a_old = 0, b_old = 0;

    double x0, y0;
    double a, b;
    unsigned int i;
    double a2, b2;
    unsigned int * mapBuff;
    mapBuff = malloc(sizeof *mapBuff * 2 * escape_limit);

    for (y = 0; y < y_resolution; y++) {
        if (y % (int) (y_resolution / 64) == 0) progress_bar_update((double) y / (double) y_resolution);
        for (x = 0; x < x_resolution; x++) {
            x0 = (x - half_x) * scalar;
            y0 = (y - half_x) * scalar;

            a  = 0.0;
            b  = 0.0;
            i  = 0;
            a2 = 0.0;
            b2 = 0.0;

            if (a2 + b2 > 4.0) continue;
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

               mapBuff[2*i]   = (int) rint(a / scalar + half_x);
               mapBuff[2*i+1] = (int) rint(b / scalar + half_y);

               if(a2 + b2 > 4.0) break;

               i++;
            }

            if(i == escape_limit) continue;
            data_write(mapBuff, data, i, x_resolution);
        }
    }
    free(mapBuff);
}

