
OPTS=-ansi -g -Wpedantic

root: main.o trie.o
	gcc ${OPTS} -o root main.o trie.o	

main.o: main.c trie.h
	gcc ${OPTS} -c main.c 

trie.o: trie.c trie.h
	gcc ${OPTS} -c trie.c	

clean:
	rm -rfv *.o root
