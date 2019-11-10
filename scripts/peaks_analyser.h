#ifndef PEAKS_ANALYSER_H
    #define PEAKS_ANALYSER_H

    #include <complex.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <float.h>
    #include <math.h>

    #include "frequency_bin_typedef.h"
    
    //The minimum ratio of the amplitude of a frequency, relative
    //to that of similar frequencies, which would add it to the list of notes.
    #define PD_NOTE_THRESHOLD 2.5
    //The size of the array used to calculate the average amplitude of frequencies
    #define PD_AVRG_AMPLITUDE_ARR_SIZE 75
    //The size of the array that holds all the possible notes of the pitch of the audio
    #define PD_NOTES_ARR_SIZE 20

    frequency_bin* get_notes(const double complex frame[], size_t frame_size, size_t sample_rate, size_t bit_depth);

#endif
