#define the link target
linkTarget= qbRay

#define the libraries that we need
LIBS= -LIBS2

SDL2PATH= C:\Users\SAM\Desktop\folders\academics_prac\Projects\Ray-Tracing-\SDL2

#define any flags. if working with cygwin in windows don't put the whole path in to the path.
CFLAGS= -std=c++17 -Ofast -I"$(SDL2PATH)\include" -L"$(SDL2PATH)\lib" -Wall -lmingw32 -lSDL2main -lSDL2

#define the object files that we need to use.
objects= main.o\
		 CApp.o\
		 $(patsubst %.cpp, %.o, $(wildcard ./qbRayTrace/primitives/*.cpp))\
		 $(patsubst %.cpp, %.o, $(wildcard ./qbRayTrace/materials/*.cpp))\
		 $(patsubst %.cpp, %.o, $(wildcard ./qbRayTrace/lights/*.cpp))\
		 $(patsubst %.cpp, %.o, $(wildcard ./qbRayTrace/utils/*.cpp))\
		 $(patsubst %.cpp, %.o, $(wildcard ./qbRayTrace/*.cpp))\

#Define the rebuildables
rebuildables= $(objects) $(linkTarget)

#Rule to actually perform the build.
$(linkTarget):$(objects)
	g++ -g -o $(linkTarget) $(objects) $(CFLAGS)

#Rule to craet the .o (objet) files
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)
.PHONEY :
clean:
	rm $(rebuildables)