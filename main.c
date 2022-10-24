#include <stdlib.h>

#include "freq_map.h"
#include "gen_ppm.h"
#include "importance_map.h"

int main() {

    char * name = "test.ppm";
    char * com = "# ";

    unsigned int x_resolution = 2560;
    unsigned int y_resolution = 2560;
    y_resolution += (y_resolution % 2 == 0);
    const unsigned int escape_limit = 512;

    unsigned int * data;
    data = (unsigned int *) malloc(sizeof(unsigned int) * x_resolution * y_resolution);

    //freq_map(x_resolution, y_resolution, escape_limit, data);
    importance_map(x_resolution, y_resolution, escape_limit, data);
    gen_ppm(name, com, x_resolution, y_resolution-1, data);
    free(data);
    return 0;
}