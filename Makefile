#Makefile for Ampersand 3D

COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror 
LINKER = g++

amp3d.o : amp3d.cpp amp3d.h
	$(COMPILER) $(COMPILER_FLAGS)  amp3d.cpp 
amp3d : amp3d.o
	$(LINKER)  amp3d.o  -llua -lglfw -framework Cocoa -framework OpenGL -framework IOKit -o  amp3d

clean :
	-rm -f *.o amp3d

