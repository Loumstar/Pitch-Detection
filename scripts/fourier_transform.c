#include "fourier_transform.h"

void print_complex_array(const double complex complex_arr[], size_t s){
    for(size_t j = 0; j < s; j++){
        printf("%.3f + %.3fi\n", creal(complex_arr[j]), cimag(complex_arr[j]));
    }
}

double complex* copy_signal(const double complex sample[], size_t n){
    //method to duplicate a signal with double complex typedef
    double complex* copy = malloc(sizeof(double complex) * n);
    for(size_t a = 0; a < n; a++){
        copy[a] = sample[a];
    }
    return copy;
}
 
void fft(double complex sample[], double complex copy[], size_t n, size_t step){
    /*
    Method to convert a sample from time domain to frequency domain, 
    using Fast Fourier Transform.

    This method is based on the Cooley-Turkey method.
    */
    if(step < n){
        fft(copy, sample, n, step * 2);
        fft(copy + step, sample + step, n, step * 2);
        
        double complex c1, c2;

        for(size_t a = 0; a < n; a += 2 * step){
            c1 = cexp(-I * M_PI * a / n);
            c2 = copy[a + step];

            sample[a / 2] = copy[a] + (c1 * c2);
            sample[(a + n) / 2] = copy[a] - (c1 * c2);
        }
    }
}

void convert_to_frequency_domain(double complex sample[], int sample_array_size){
    //copy the signal
    double complex* copy = copy_signal(sample, sample_array_size);
    //runs fourier transform
    fft(sample, copy, sample_array_size, 1);
    free(copy);
    //removes offset represented by the double complex value at 0 Hz
    sample[0] = 0;
}
