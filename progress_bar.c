//
// Created by TJ on 10/23/2022.
//

#include "progress_bar.h"

void pbar_terminate() {
    printf("\r");
    printf("[----------------------------COMPLETE----------------------------]");
    printf("\r\n");
    fflush(stdout);
}

void progress_bar_update(double input) {
    printf("\r");
    printf("[");
    for (int i = 0; i < 64.0 * (double) input; i++) {
        printf("#");
    }
    fflush(stdout);
}

void progress_bar_init() {
    printf("[");
    for (int i = 0; i < 64; i++) {
        printf("-");
    }
    printf("]");
    fflush(stdout);
}