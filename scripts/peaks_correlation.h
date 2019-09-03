#ifndef PEAKS_CORRELATION_H
    #define PEAKS_CORRELATION_H

    #include <math.h>

    #include "frequency_bin_typedef.h"

    #define PD_NORMAL_DIST_WIDTH 100.0
    #define PD_HARMONICS_ARR_SIZE 20

    void get_note_probabilities(frequency_bin notes[], size_t notes_array_size);

#endif