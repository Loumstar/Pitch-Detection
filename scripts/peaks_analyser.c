#include "peaks_analyser.h"

bool amplitude_is_maxima(double a0, double a1, double a2){
    return (a1 - a0 > FLT_EPSILON) && (a1 - a2 > FLT_EPSILON);
}

bool amplitude_is_above_threshold(double a, double average_amplitude){
    return a / average_amplitude > PD_NOTE_THRESHOLD;
}

double get_amplitude(const double complex z, const size_t frame_size){
    return cabs(z) * 2 / frame_size;
}

double decibels(double v, const size_t bit_depth){
    //base voltage is one as the amplitude is scaled to between 0 and 1.
    return 20 * log10f(v / pow(2, bit_depth));
}

double get_average_amplitude(int f, const double complex frame[], const size_t frame_size){
    /*
    Method to determine the amplitude of frequencies surrounding the amplitude at f (average_amplitude).

    The average_amplitude is calculated by summing the amplitudes that are within the set of frequencies 
    surrounding f, and is divided by the number of amplitudes in the set.
    */
    double sum = 0;
    size_t lb, ub;
    //if the set indices fall outside the upper bound of frame
    if(f + floor(PD_AVRG_AMPLITUDE_ARR_SIZE / 2) > frame_size){
        //use the last set of values that make a full set.
        lb = frame_size - PD_AVRG_AMPLITUDE_ARR_SIZE;
        ub = frame_size;
    //if the set indices fall outside the upper bound of frame 
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
        sum += get_amplitude(frame[i], frame_size);
    }
    //divide by the size of the frame.
    return sum / PD_AVRG_AMPLITUDE_ARR_SIZE;
}

frequency_bin* get_notes(const double complex frame[], const size_t frame_size, size_t sample_rate, const size_t bit_depth){
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
    double next_amplitude = get_amplitude(frame[1], frame_size);

    size_t i = 0;
    
    for(size_t f = 1; f < floor(frame_size / 2); f++){
        average_amplitude = get_average_amplitude(f, frame, frame_size);
        
        prev_amplitude = amplitude;
        amplitude = next_amplitude;
        next_amplitude = get_amplitude(frame[f+1], frame_size);

        if(
            i < PD_NOTES_ARR_SIZE //avoids overfilling array and segfaults
            && amplitude > 1 //must be as signal was int type, so smallest amplitude value is 1
            && amplitude_is_maxima(prev_amplitude, amplitude, next_amplitude)
            && amplitude_is_above_threshold(amplitude, average_amplitude)
        ){
            notes[i][0] = f * sample_rate / frame_size;
            notes[i][1] = decibels(amplitude, bit_depth);
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
