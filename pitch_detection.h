#ifndef PITCH_DETECTION_H
    #define PITCH_DETECTION_H

    #include <complex.h>
    #include <string.h>

    #include "scripts/fourier_transform.h"
    #include "scripts/peaks_correlation.h"
    #include "scripts/peaks_analyser.h"

    frequency_bin* get_pitches(double complex sample[], size_t sample_size, size_t sample_rate, size_t bit_depth);

    void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin);

    double get_pitch(double complex sample[], size_t sample_size, size_t sample_rate, size_t bit_depth);

#endif
