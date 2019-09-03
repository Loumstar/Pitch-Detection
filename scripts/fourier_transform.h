#ifndef FOURIER_TRANSFORM_H
    #define FOURIER_TRANSFORM_H

    #include <stdio.h>
    #include <stdlib.h>

    #include "../../int_complex/int_complex.h"
    #include "../../double_complex/double_complex.h"

    void convert_to_frequency_domain(int_complex sample[], int sample_array_size);

#endif