#include "fourier_transform.h"

void print_complex_array(const double complex complex_arr[], size_t n){
    for(size_t j = 0; j < n; j++){
        printf("%.3f + %.3fi\n", creal(complex_arr[j]), cimag(complex_arr[j]));
    }
}

double complex* copy_signal(const double complex frame[], size_t n){
    //method to duplicate a signal with double complex typedef
    double complex* frame_copy = malloc(sizeof(double complex) * n);
    for(size_t a = 0; a < n; a++){
        frame_copy[a] = frame[a];
    }
    return frame_copy;
}
 
void fft(double complex frame[], double complex frame_copy[], size_t n, size_t step){
    /*
    Method to convert a frame from time domain to frequency domain, 
    using Fast Fourier Transform.

    This method is based on the Cooley-Turkey method.
    */
    if(step < n){
        fft(frame_copy, frame, n, step * 2);
        fft(frame_copy + step, frame + step, n, step * 2);
        
        double complex c1, c2;

        for(size_t a = 0; a < n; a += 2 * step){
            c1 = cexp(-I * M_PI * a / n);
            c2 = frame_copy[a + step];

            frame[a / 2] = frame_copy[a] + (c1 * c2);
            frame[(a + n) / 2] = frame_copy[a] - (c1 * c2);
        }
    }
}

void convert_to_frequency_domain(double complex frame[], int frame_size){
    //frame_copy the signal
    double complex* frame_copy = copy_signal(frame, frame_size);
    //runs fourier transform
    fft(frame, frame_copy, frame_size, 1);
    free(frame_copy);
    //removes offset represented by the double complex value at 0 Hz
    frame[0] = 0;
}
