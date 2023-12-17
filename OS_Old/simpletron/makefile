COMPILE = gcc -c
OUTPUT = gcc -o
ARCHIVE = ar cr

simple.exe: simple.o libsimple.a 
	$(OUTPUT) simple.exe simple.o -L. -lsimple

simple.o: simple.c simple.h
	$(COMPILE) simple.c

util.o: util.c
	$(COMPILE) util.c

libsimple.a: util.o
	$(ARCHIVE) libsimple.a util.o

clean:
	rm *.o libsimple.a