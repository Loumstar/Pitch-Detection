CC = gcc
CFLAGS = -pedantic -Wall

EXECUTABLES = testPitchDetection
INCLUDES = -I./C-UnitTest/ -I../ -I../scripts/

# Executable
testPitchDetection: pitch_detection.test.o pitch_detection.o fourier_transform.o frequency_bin_typedef.o peaks_analyser.o peaks_correlation.o unittest.o
	$(CC) $(CFLAGS) -o testPitchDetection pitch_detection.test.o pitch_detection.o fourier_transform.o frequency_bin_typedef.o peaks_analyser.o peaks_correlation.o unittest.o

# Object Files
pitch_detection.test.o: pitch_detection.test.c
	$(CC) $(CFLAGS) $(INCLUDES) -o pitch_detection.test.o -c pitch_detection.test.c

pitch_detection.o: ../pitch_detection.c
	$(CC) $(CFLAGS) $(INCLUDES) -o pitch_detection.o -c ../pitch_detection.c

fourier_transform.o: ../scripts/fourier_transform.c
	$(CC) $(CFLAGS) $(INCLUDES) -o fourier_transform.o -c ../scripts/fourier_transform.c

frequency_bin_typedef.o: ../scripts/frequency_bin_typedef.c
	$(CC) $(CFLAGS) $(INCLUDES) -o frequency_bin_typedef.o -c ../scripts/frequency_bin_typedef.c

peaks_analyser.o: ../scripts/peaks_analyser.c
	$(CC) $(CFLAGS) $(INCLUDES) -o peaks_analyser.o -c ../scripts/peaks_analyser.c

peaks_correlation.o: ../scripts/peaks_correlation.c
	$(CC) $(CFLAGS) $(INCLUDES) -o peaks_correlation.o -c ../scripts/peaks_correlation.c

unittest.o: C-UnitTest/unittest.c
	$(CC) $(CFLAGS) $(INCLUDES) -o unittest.o -c C-UnitTest/unittest.c

.PHONY: clean, all

clean:
	rm -v *.o $(EXECUTABLES)

all:
	make $(EXECUTABLES)