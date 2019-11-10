#include "pitch_detection.h"

frequency_bin* get_pitches(double complex frame[], size_t frame_size, size_t sample_rate, size_t bit_depth){
    //method that returns an array of pitch bins that are possible notes of the audio
    convert_to_frequency_domain(frame, frame_size);
    frequency_bin* notes = get_notes(frame, frame_size, sample_rate, bit_depth);
    
    if(notes) get_note_probabilities(notes, PD_NOTES_ARR_SIZE);

    return notes;
}

void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin){
    //method that returns the pitch bin with the greatest probability
    double max_probability = 0;
    size_t j;

    for(size_t i = 0; i < PD_NOTES_ARR_SIZE; i++){
        if(max_probability < notes[i][2]){
            max_probability = notes[i][2];
            j = i;
        }
    }
    if(max_probability) memcpy(pitch_bin, notes[j], FREQUENCY_BIN_SIZE);
    else memcpy(pitch_bin, NULL_FREQ_BIN, FREQUENCY_BIN_SIZE);
}

double get_pitch(double complex frame[], size_t frame_size, size_t sample_rate, size_t bit_depth){
    //method that returns the most probable pitch of the audio.
    frequency_bin* notes = get_pitches(frame, frame_size, sample_rate, bit_depth);
    frequency_bin bin;
    
    get_pitch_bin(notes, bin);
    free(notes);

    return bin[0];
}
