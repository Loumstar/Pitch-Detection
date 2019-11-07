CC = gcc
CFLAGS = -pedantic -Wall

EXECUTABLES = testPitchDetection

OBJECT_FILES = \
	pitch_detection.test.o \
	pitch_detection.o \
	fourier_transform.o \
	frequency_bin_typedef.o \
	peaks_analyser.o \
	peaks_correlation.o

UNITTEST_O = ./tests/C-UnitTest/unittest.o

# Test Executable
testPitchDetection: $(OBJECT_FILES)
	$(CC) -o testPitchDetection $(OBJECT_FILES) $(UNITTEST_O)

# Test object file
pitch_detection.test.o: tests/pitch_detection.test.c
	$(CC) $(CFLAGS) -o pitch_detection.test.o -c tests/pitch_detection.test.c	

# Main object file
pitch_detection.o: pitch_detection.c
	$(CC) $(CFLAGS) -o pitch_detection.o -c pitch_detection.c

# Supporting libraries
fourier_transform.o: scripts/fourier_transform.c
	$(CC) $(CFLAGS) -o fourier_transform.o -c scripts/fourier_transform.c

frequency_bin_typedef.o: scripts/frequency_bin_typedef.c
	$(CC) $(CFLAGS) -o frequency_bin_typedef.o -c scripts/frequency_bin_typedef.c

peaks_analyser.o: scripts/peaks_analyser.c
	$(CC) $(CFLAGS) -o peaks_analyser.o -c scripts/peaks_analyser.c

peaks_correlation.o: scripts/peaks_correlation.c
	$(CC) $(CFLAGS) -o peaks_correlation.o -c scripts/peaks_correlation.c

# Misc
.PHONY: clean, all

clean:
	rm -v $(EXECUTABLES) $(OBJECT_FILES)

all: $(EXECUTABLES) $(OBJECT_FILES)