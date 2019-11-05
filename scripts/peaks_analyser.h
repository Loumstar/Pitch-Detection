#ifndef PEAKS_ANALYSER_H
    #define PEAKS_ANALYSER_H

    #include <complex.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <float.h>
    #include <math.h>

    #include "frequency_bin_typedef.h"

    //Number of frames recorded per second (typically 44.1kHz for CD).
    #define PD_SAMPLE_RATE 2560
    //The number of values each frame can take tp describe the waveform.
    #define PD_SAMPLE_BIT_DEPTH 1024
    //The number of frames in a sample. Must be a power of two.
    #define PD_SAMPLE_ARR_SIZE 512
    //The minimum ratio of the amplitude of a frequency, relative
    //to that of similar frequencies, which would add it to the list of notes.
    #define PD_NOTE_THRESHOLD 2.5
    //The size of the array used to calculate the average amplitude of frequencies
    #define PD_AVRG_AMPLITUDE_ARR_SIZE 75
    //The size of the array that holds all the possible notes of the pitch of the audio
    #define PD_NOTES_ARR_SIZE 20

    frequency_bin* get_notes(const double complex sample[]);

#endif
