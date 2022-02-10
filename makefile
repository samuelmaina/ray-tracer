#define the link target
linkTarget= qbRay

#define the libraries that we need
LIBS= -LIBS2

#define any flags. if working with cygwin in windows don't put the whole path in to the path.
CFLAGS= -std=c++17 -Ofast -I"C:\Users\SAM\Desktop\folders\academics_prac\Projects\Ray-Tracing-\SDL2\include" -L"C:\Users\SAM\Desktop\folders\academics_prac\Projects\Ray-Tracing-\SDL2\lib" -Wall -lmingw32 -lSDL2main -lSDL2

#define the object files that we need to use.
objects= main.o\
		 CApp.o\
		 $(patsubst %.cpp, %.o, $(wildcard ./qbRayTrace/*.cpp))

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