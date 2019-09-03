#include <math.h>

#include "frequency_bin_typedef.h"

#define PD_NORMAL_DIST_WIDTH 100.0
#define PD_HARMONICS_ARR_SIZE 20

double* get_harmonics(double f){
    //method to return an array of frequencies that are harmonics of a frequency.
    double* harmonics = malloc(sizeof(double) * PD_HARMONICS_ARR_SIZE);
    if(!harmonics) return NULL;
    
    for(size_t h = 0; h < PD_HARMONICS_ARR_SIZE; h++){
        harmonics[h] = f * (h + 1);
    }
    return harmonics;
}

double get_correlation(double f, frequency_bin notes[], size_t notes_array_size){
    /*
    Method that returns a value that indicates how well a frequency f fits the set of peaks (notes) found.
    
    This is done by using a variation on the normal distribution, where each peak has a bell curve
    and the correlation value returned is given by the probability at that point.
    */
    double c = 0;
    for(size_t s = 0; s < notes_array_size; s++){
        if(!isnan(notes[s][0])){
            c += pow(M_E, -1 * pow((4 * (f - notes[s][0]) / PD_NORMAL_DIST_WIDTH), 2));
        }
    }
    return c;
}

double test_harmonics(frequency_bin notes[], double harmonics[], size_t notes_array_size){
    //method to run get_correlation() for a set of harmonics.
    double correlation = 0;
    for(size_t h = 0; h < PD_HARMONICS_ARR_SIZE; h++){
        correlation += get_correlation(harmonics[h], notes, notes_array_size);
    }
    return correlation / PD_HARMONICS_ARR_SIZE;
}

void get_note_probabilities(frequency_bin notes[], size_t notes_array_size){
    /*
    Method that adds the probability of a frequency bin being the note of the audio
    to the last column in the frequency bin array.

    This is done by determining the harmonics of the frequency bin and comparing how well
    they fit all the notes in the spectrum.
    */
    double probability;
    for(int p = 0; p < notes_array_size; p++){
        if(!isnan(notes[p][0])){
            double* harmonics = get_harmonics(notes[p][0]);
            
            if(!harmonics) break;

            probability = test_harmonics(notes, harmonics, notes_array_size);
            free(harmonics);

            notes[p][2] = probability;
        }
    }
}