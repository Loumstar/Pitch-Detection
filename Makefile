CC = gcc
CFLAGS = -pedantic -Wall

OBJECT_FILES = pitch_detection.o \
			   fourier_transform.o \
			   frequency_bin_typedef.o \
			   peaks_analyser.o \
			   peaks_correlation.o

INCLUDES = -I./scripts/

# Main object file
pitch_detection.o: pitch_detection.c
	$(CC) $(CFLAGS) $(INCLUDES) -o pitch_detection.o -c pitch_detection.c

# Supporting libraries
fourier_transform.o: scripts/fourier_transform.c
	$(CC) $(CFLAGS) $(INCLUDES) -o fourier_transform.o -c scripts/fourier_transform.c

frequency_bin_typedef.o: scripts/frequency_bin_typedef.c
	$(CC) $(CFLAGS) $(INCLUDES) -o frequency_bin_typedef.o -c scripts/frequency_bin_typedef.c

peaks_analyser.o: scripts/peaks_analyser.c
	$(CC) $(CFLAGS) $(INCLUDES) -o peaks_analyser.o -c scripts/peaks_analyser.c

peaks_correlation.o: scripts/peaks_correlation.c
	$(CC) $(CFLAGS) $(INCLUDES) -o peaks_correlation.o -c scripts/peaks_correlation.c

# Misc
.PHONY: clean, all

clean:
	rm -v $(OBJECT_FILES)

all:
	make $(OBJECT_FILES)