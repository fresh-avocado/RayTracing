CPP = g++
CPPFLAGS = -std=c++20 -Wall -Wpedantic -Wextra -Wshadow -I /opt/X11/include -L /opt/X11/lib -lX11 -ljpeg -lpng -lz
# TODO: poner paths si lo organizo en carpetas
# VPATH = ./src:./src/avl:./src/utils:./tests

all: main.o camara.o cimg.o luz.o mundo.o objeto.o rayo.o vector.o
	$(CPP) $(CPPFLAGS) main.o camara.o cimg.o luz.o mundo.o objeto.o rayo.o vector.o

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o

camara.o: Camara.h Camara.cpp
	$(CPP) $(CPPFLAGS) -c Camara.cpp -o camara.o

cimg.o: CImg.h
	$(CPP) $(CPPFLAGS) -c CImg.h -o cimg.o

luz.o: Luz.h Luz.cpp
	$(CPP) $(CPPFLAGS) -c Luz.cpp -o luz.o

mundo.o: Mundo.h Mundo.cpp
	$(CPP) $(CPPFLAGS) -c Mundo.cpp -o mundo.o

objeto.o: Objeto.h Objeto.cpp
	$(CPP) $(CPPFLAGS) -c Objeto.cpp -o objeto.o

rayo.o: Rayo.h Rayo.cpp
	$(CPP) $(CPPFLAGS) -c Rayo.cpp -o rayo.o

vector.o: vector.h vector.cpp
	$(CPP) $(CPPFLAGS) -c vector.cpp -o vector.o

clean:
	rm *.o a.out