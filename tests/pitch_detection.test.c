#include <stdbool.h>
#include <complex.h>
#include <time.h>
#include <math.h>

#include "C-UnitTest/unittest.h"
#include "../scripts/frequency_bin_typedef.h"
#include "../pitch_detection.h"

bool is_power_of_two(int x){
    return (x & (x - 1)) == 0;
}

double complex* create_signal(const double a[3][2], size_t sample_size, size_t sample_rate, double offset, size_t length){
    /*
    Method to return an array of values that make up an oscillation.
    
    The oscillation can be a combination of frequencies and volumes and are returned
    as a double complex datatype with only real components, so fft can be applied to it.
    */
    double complex* sample_signal = malloc(sizeof(double complex) * sample_size);
    for(size_t i = 0; i < sample_size; i++){
        int sum = 0;
        for(size_t j = 0; j < length; j++){
            sum += a[j][1] * sin((double) 2 * M_PI * a[j][0] * i / sample_rate);
        }
        sample_signal[i] = sum + offset;
    }
    return sample_signal;
}

int main(void){
    clock_t main_start = clock();
    clock_t start, end;

    size_t sample_size = 512;
    size_t bit_depth = 8;
    size_t sample_rate = 2560;

    double frequency_resolution = sample_rate / sample_size;
    
    if(!is_power_of_two(sample_size)){
        printf("The number of frames in the clip must be a power of two.\n");
        return 1;
    }

    //Output basic properties of the transform.
    printf("The maximum frequency measured is %i Hz.\n", (int) sample_rate / 2);
    printf("The frequency resolution is %.1f Hz.\n", frequency_resolution);
    printf("The length of the clip is %.3fs.\n\n", (double) sample_size / sample_rate);

    //example basic waveform.  
    size_t a_size = 3;   
    
    double a[3][2] = {
        {125, 128},
        {250, 40},
        {510, 60}
    };

    //measure time taken to create the 125 Hz signal.
    start = clock();
    double complex* sample_signal = create_signal(a, sample_size, sample_rate, 0, a_size);
    end = clock();

    printf("Signal created in %.3f ms.\n", (double) (end - start) / CLOCKS_PER_SEC * 1000);
    if(!sample_signal) return 1;

    //Measure time taken to determine all possible pitches
    start = clock();
    frequency_bin* notes = get_pitches(sample_signal, sample_size, sample_rate, bit_depth);
    end = clock();

    printf("Signal analysed in %.3f ms.\n\n", (double) (end - start) / CLOCKS_PER_SEC * 1000);
    
    //Find the most probable pitch bin
    frequency_bin pitch_bin;
    get_pitch_bin(notes, pitch_bin);

    free(sample_signal);
    
    if(!notes) return 1;

    print_frequency_bins(notes, PD_NOTES_ARR_SIZE);
    printf("\n");
    print_frequency_bins(&pitch_bin, 1);
    free(notes);

    double volume = pitch_bin[1];
    double pitch = pitch_bin[0];

    //Test whether pitch and volume are correct
    printf("\nAssert that pitch detected is %d ± %d Hz\n", (int) a[0][0], (int) frequency_resolution);
    printf("    %.f\n", pitch);
    if(assert_double_similar(pitch, 125.0, frequency_resolution / 2)){
        printf("    PASS\n\n");
    } else {
        printf("    FAIL\n\n");
        return 1;
    }

    printf("Assert that volume detected is %.3f ± 1 dB\n", 20 * log10f(a[0][1] / pow(2, bit_depth)));
    printf("    %.3f\n", volume);
    if(assert_double_similar(volume, 20 * log10f(a[0][1] / pow(2, bit_depth)), 1)){
        printf("    PASS\n\n");
    } else {
        printf("    FAIL\n\n");
        return 1;
    }
    
    clock_t main_end = clock();
    printf("Test completed in %.3f ms.\n", (double) (main_end - main_start) / CLOCKS_PER_SEC * 1000);
    
    return 0;
}
