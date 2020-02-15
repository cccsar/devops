
test: main.o adymat.o 
	g++ -o test main.o adymat.o

main.o: main.cpp adymat.h
	g++ -c main.cpp

adymat.o: adymat.cpp adymat.h
	g++ -c adymat.cpp

clean: 
	rm -rfv *.o test
