CFLAGS = -ansi -pedantic -lm
SDL =  `sdl-config --cflags --libs`

all: tnelturtle.c tdraw.o tdraw.h
	gcc tnelturtle.c tdraw.o $(CFLAGS) $(SDL) -o tnelturtle.out -llua
	strip -s tnelturtle.out
	du -b tnelturtle.out

tdraw.o : tdraw.c tdraw.h
	gcc -c tdraw.c $(CFLAGS) $(SDL) -o tdraw.o
