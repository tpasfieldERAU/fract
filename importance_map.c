//
// Created by TJ on 10/24/2022.
//

#include "importance_map.h"

void write_im_map(
        const unsigned int *buffer,
        unsigned int *data,
        unsigned int i,
        unsigned int x_resolution,
        unsigned int x,
        unsigned int y,
        const unsigned int x_range[2],
        const unsigned int y_range[2]
){
    unsigned int iX, iY;

    for (int s = 1; s < i; s++) {
        iX = buffer[2*s];
        iY = buffer[2*s+1];
        if (iX>=x_range[0] && iX<=x_range[1]){
            if (iY>=y_range[0] && iY<=y_range[1]) {
                data[x_resolution*y+x] += 1;
            }
        }
    }
}

void importance_map(
        const unsigned int x_resolution,
        const unsigned int y_resolution,
        unsigned int escape_limit,
        unsigned int *data
) {
    const double half_x = x_resolution / 2.0, half_y = y_resolution / 2.0, scalar = 4.0 / y_resolution;
    unsigned int x, y;
    int conv_test_var = 0;
    double a_old = 0, b_old = 0;

    double x0, y0;
    double a, b;
    unsigned int i;
    double a2, b2;

    unsigned int x_range[2] = {(int) rint(half_x) - (int) rint(x_resolution / 16.0),
                               (int) rint(half_x) + (int) rint(x_resolution / 16.0)};
    unsigned int y_range[2] = {(int) rint(y_resolution * 0.25) - (int) rint(y_resolution / 16.0),
                               (int) rint(y_resolution * 0.25) + (int) rint(y_resolution / 16.0)};


    for (y = 0; y < y_resolution; y++) {
        for (x = 0; x < x_resolution; x++) {
            unsigned int *buffer;
            buffer = malloc(sizeof *buffer * 2 * escape_limit);

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

                buffer[2*i]   = (int) rint(a / scalar + half_x);
                buffer[2*i+1] = (int) rint(b / scalar + half_y);

                if(a2 + b2 > 4.0) break;

                i++;
            }

            if(i == escape_limit){
                free(buffer);
                continue;
            }
            write_im_map(buffer, data, i, x_resolution, x, y, x_range, y_range);
            free(buffer);
        }
    }
}