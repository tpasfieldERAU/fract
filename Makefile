CC=gcc
CFLAGS=-lm -I.
FILES = main.c gen_ppm.c freq_map.c data_write.c progress_bar.c gen_pgm.c

testing: $(FILES)
	$(CC) -o $@ $^ $(CFLAGS)  
