CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic
debug: CFLAGS += -g
INCS = parse.h structure.h
SRCS = parse.c structure.c hospital.c
OBJ = $(SRCS:.c=.o)
LIBS = 

%.o: %.c $(INCS)
	$(CC) -c -o $@ $< $(CFLAGS)

hospital: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm -rf *.o

debug: hospital
	objcopy --only-keep-debug hospital hospital.dbg

.PHONY: clean

clean:
	rm -rf *.o *.dbg hospital