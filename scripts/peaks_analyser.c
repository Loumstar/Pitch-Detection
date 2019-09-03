#include "peaks_analyser.h"

bool amplitude_is_maxima(double a0, double a1, double a2){
    return (a1 - a0 > FLT_EPSILON) && (a1 - a2 > FLT_EPSILON);
}

bool amplitude_is_above_threshold(double a, double average_amplitude){
    return a / average_amplitude > PD_NOTE_THRESHOLD;
}

double get_amplitude(const int_complex z){
    return cabs(z) * 2 / PD_SAMPLE_ARR_SIZE;
}

double decibels(double v){
    //base voltage is one as the amplitude is scaled to between 0 and 1.
    return 20 * log10f(v / PD_SAMPLE_BIT_DEPTH);
}

double get_average_amplitude(int f, const int_complex sample[]){
    /*
    Method to determine the amplitude of frequencies surrounding the amplitude at f (average_amplitude).

    The average_amplitude is calculated by summing the amplitudes that are within the set of frequencies 
    surrounding f, and is divided by the number of amplitudes in the set.
    */
    double sum = 0;
    size_t lb, ub;
    //if the set indices fall outside the upper bound of sample
    if(f + floor(PD_AVRG_AMPLITUDE_ARR_SIZE / 2) > PD_SAMPLE_ARR_SIZE){
        //use the last set of values that make a full set.
        lb = PD_SAMPLE_ARR_SIZE - PD_AVRG_AMPLITUDE_ARR_SIZE;
        ub = PD_SAMPLE_ARR_SIZE;
    //if the set indices fall outside the upper bound of sample 
    } else if(f - floor(PD_AVRG_AMPLITUDE_ARR_SIZE / 2) < 0){
        //use the first set of values that make a full set.
        lb = 0;
        ub = PD_AVRG_AMPLITUDE_ARR_SIZE;
    } else {
        //else use a set where f is the middle value.
        lb = f - floor(PD_AVRG_AMPLITUDE_ARR_SIZE / 2);
        ub = f + floor(PD_AVRG_AMPLITUDE_ARR_SIZE / 2);
    }
    for(size_t i = lb; i < ub; i++){
        //sum the values
        sum += get_amplitude(sample[i]);
    }
    //divide by the size of the sample.
    return sum / PD_AVRG_AMPLITUDE_ARR_SIZE;
}

frequency_bin* get_notes(const int_complex sample[]){
    /*
    Method to determine the peak frequencies of a frequency spectrum, which are possible
    notes of the audio.

    If the amplitude of that frequency is a local maxima and the ratio between its
    amplitude and the average amplitude of surrounding frequencies (see get_average_amplitude())
    is greater than the PD_NOTE_THRESHOLD then it is added to the array.
    */
    frequency_bin* notes = malloc(FREQUENCY_BIN_SIZE * PD_NOTES_ARR_SIZE);
    if(!notes) return NULL;
    
    double average_amplitude, prev_amplitude;

    double amplitude = 0;
    double next_amplitude = get_amplitude(sample[1]);

    size_t i = 0;
    
    for(size_t f = 1; f < floor(PD_SAMPLE_ARR_SIZE / 2); f++){
        average_amplitude = get_average_amplitude(f, sample);
        
        prev_amplitude = amplitude;
        amplitude = next_amplitude;
        next_amplitude = get_amplitude(sample[f+1]);

        if(
            i < PD_NOTES_ARR_SIZE //avoids overfilling array and segfaults
            && amplitude > 1 //must be as signal was int type, so smallest amplitude value is 1
            && amplitude_is_maxima(prev_amplitude, amplitude, next_amplitude)
            && amplitude_is_above_threshold(amplitude, average_amplitude)
        ){
            notes[i][0] = f * PD_SAMPLE_RATE / PD_SAMPLE_ARR_SIZE;
            notes[i][1] = decibels(amplitude);
            i++;
        }
    }
    while(i < PD_NOTES_ARR_SIZE){ 
        //initialises unused positions in notes[] to a a standard form.
        memcpy(notes[i], NULL_FREQ_BIN, FREQUENCY_BIN_SIZE);
        i++;
    }
    return notes;
}