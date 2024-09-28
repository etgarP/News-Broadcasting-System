.PHONY: all clean

all: main

main: BoundedBuffer.o Dispacher.o Producer.o ProducersList.o UnboundedBuffer.o coEditor.o screenManager.o main.o
	gcc -o main BoundedBuffer.o Dispacher.o Producer.o ProducersList.o UnboundedBuffer.o coEditor.o screenManager.o main.o

BoundedBuffer.o: BoundedBuffer.c BoundedBuffer.h
	gcc -c BoundedBuffer.c

Dispacher.o: Dispacher.c Dispacher.h
	gcc -c Dispacher.c

Producer.o: Producer.c Producer.h
	gcc -c Producer.c

ProducersList.o: ProducersList.c ProducersList.h
	gcc -c ProducersList.c

UnboundedBuffer.o: UnboundedBuffer.c UnboundedBuffer.h
	gcc -c UnboundedBuffer.c

coEditor.o: coEditor.c coEditor.h
	gcc -c coEditor.c

screenManager.o: screenManager.c
	gcc -c screenManager.c

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o main