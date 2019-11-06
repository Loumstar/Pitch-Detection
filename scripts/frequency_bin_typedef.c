#include "frequency_bin_typedef.h"

const frequency_bin NULL_FREQ_BIN = {NAN, -INFINITY, NAN};

void print_frequency_bins(const frequency_bin bin[], size_t n){
    //method to print info of each frequency bin to the console
    for(size_t j = 0; j < n; j++){    
        if(!isnan(bin[j][0])){
            printf("(%.f Hz, %.2f dB, %.4f)\n", bin[j][0], bin[j][1], bin[j][2]);
        }
    }
}
