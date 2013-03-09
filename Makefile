#Makefile for Ampersand 3D

COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall 
LINKER = g++

amp3d.o : amp3d.cpp amp3d.h
	$(COMPILER) $(COMPILER_FLAGS)  amp3d.cpp 
renderer.o : renderer.cpp renderer.h
	$(COMPILER) $(COMPILER_FLAGS)  renderer.cpp
lodepng.o : lodepng.cpp lodepng.h
	$(COMPILER) $(COMPILER_FLAGS)  lodepng.cpp 
amp3d : amp3d.o renderer.o lodepng.o
	$(LINKER)  amp3d.o renderer.o lodepng.o -Lslb/build/bin/static -lslb -I/usr/local/include -L/usr/local/lib -I/usr/include -L/usr/lib -L/opt/local/include/ -framework CoreFoundation -framework Cocoa -framework OpenGL -framework IOKit -o  amp3d -llua -lglfw -lglew

clean :
	-rm -f *.o amp3d

