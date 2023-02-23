all: RSA-main clean

RSA-main: RSA.o
	g++ --static -std=c++11 RSA-main.cpp RSA.o -o RSA -lntl -lgmp -lm

RSA.o: RSA.cpp RSA.h
	g++ -std=c++11 -c RSA.cpp

clean:
	rm *.o