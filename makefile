CC=gcc
CFLAGS=-Wall -Wextra 
OFLAGS=-O2 -march=native -mtune=native
LFLAGS=-lm 

TARGET=main.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.o matrice.o
	$(CC) $(LFLAGS) $^ -o $@ -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $(OFLAGS) $< -o $@

main.c: matrice.c matrice.h

matrix.c: matrice.h

clean:
	rm -Rf *~ *.o $(TARGET)
