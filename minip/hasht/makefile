
OPTS=-ansi -g -Wpedantic

root: main.o hash.o singly.o
	gcc ${OPTS} -o root main.o hash.o singly.o

main.o: main.c hash.c  
	gcc ${OPTS} -c main.c

hash.o: hash.c hash.h singly.h
	gcc ${OPTS} -c hash.c

singly.o: singly.c singly.h
	gcc ${OPTS} -c singly.c 

clean: 
	rm -rfv *.o root
