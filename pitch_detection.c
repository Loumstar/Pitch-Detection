#include "pitch_detection.h"

frequency_bin* get_pitches(int_complex sample[]){
    //method that returns an array of pitch bins that are possible notes of the audio
    convert_to_frequency_domain(sample, PD_SAMPLE_ARR_SIZE);
    frequency_bin* notes = get_notes(sample);
    
    if(notes) get_note_probabilities(notes, PD_NOTES_ARR_SIZE);

    return notes;
}

void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin){
    //method that returns the pitch bin with the greatest probability
    double max_p = 0;
    size_t j;

    for(size_t i = 0; i < PD_NOTES_ARR_SIZE; i++){
        if(!isnan(notes[i][2]) && notes[i][2] > max_p){
            max_p = notes[i][2];
            j = i;
        }
    }
    
    memcpy(pitch_bin, notes[j], FREQUENCY_BIN_SIZE);
}

double get_pitch(int_complex sample[]){
    //method that returns the most probable pitch of the audio.
    frequency_bin* notes = get_pitches(sample);
    frequency_bin bin;
    
    get_pitch_bin(notes, bin);
    free(notes);

    return bin[0];
}