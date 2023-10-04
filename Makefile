CC=gcc
CFLAGS=-lm -I.
FILES = main.c gen_ppm.c freq_map.c data_write.c progress_bar.c

testing: $(FILES)
	$(CC) -o $@ $^ $(CFLAGS)  
