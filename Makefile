
CC = g++
LD = g++

CFLAGS = -Wall -std=c++11
LFLAGS = -Wall

TRAB3OBJS = main.o catalogo.o

TRABALHOS = ./execTrab3

.cpp.o:
	$(CC) $(CFLAGS) -c $<

all: $(TRABALHOS)

execTrab3: $(TRAB3OBJS)
	$(LD) $(LFLAGS) -o $@ $(TRAB3OBJS) -lm

clean:
	rm -f *.o $(TRABALHOS)
