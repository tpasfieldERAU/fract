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
    unsigned int conv_test_var = 0;
    double a_old = 0.0, b_old = 0.0;

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
               mapBuff[2*i]   = (unsigned int) ( a / scalar + half_x);
               mapBuff[2*i+1] = (unsigned int) ( b / scalar + half_y);
               i++;
            }
            if(i == escape_limit) continue;
            data_write(mapBuff, data, i, x_resolution);
        }
    }
    free(mapBuff);
}

