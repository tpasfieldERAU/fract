#include <stdlib.h>

#include "freq_map.h"
#include "gen_ppm.h"
#include "importance_map.h"
#include "progress_bar.h"
#include "color_map.h"

int main() {
    /* Generate Progress Bar Lower Layer */
    progress_bar_init();

    /* Define info needed for writing a PPM image. Will later be moved when
     * support for other formats is added. */
    char *name = "test.ppm";
    char *com = "# ";

    unsigned int x_resolution = 2560*4;
    unsigned int y_resolution = 2560*4;
    y_resolution += (y_resolution % 2 == 0);
    unsigned int escape_limit = 8192;


    /* Define an output array. Needs to be dynamically allocated due to stack
     * memory size constraints. */
    //unsigned int *data;
    //data = (unsigned int *) calloc(x_resolution * y_resolution, sizeof(unsigned int));


    /* Calculate various forms of fractals. Outputs to inputted Data.
     *       freq_map    -    Also known as the Buddhabrot or Nebulabrot
     *                        fractal. These specific names only apply to the
     *                        frequency map of the Mandelbrot Set. This
     *                        currently only calculates the map for this case.
     *
     * importance_map    -    Calculates the map of coordinates that have
     *                        meaningful effect for a limited rendered region
     *                        of the frequency map. This will later be used
     *                        to allow for fast approximation of the frequency
     *                        map.
     */
    //freq_map(x_resolution, y_resolution, 500, data);
    //importance_map(x_resolution, y_resolution, escape_limit, data);


    /* Generate image files using data written above
     * gen_ppm    -    Generates PPM image (P6 Format)
     * [ More file formats to be added ] */
    //gen_ppm(name, com, x_resolution, y_resolution-1, data);

    //free(data);

    color_map(x_resolution, y_resolution, escape_limit);

    return 0;
}