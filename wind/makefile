all:
	g++ -c wind.cpp `wx-config --cflags` -O2 -s 
	ar -rc libimage.a wind.o
	ranlib libimage.a
clear:
	rm *.o
