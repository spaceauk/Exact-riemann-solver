SHELL = /bin/sh

# Select compiler
CMPR = g++

CPPFLAGS=$(ARG)
CPPFLAGS +=  

CPP = 
CFLAGS = 

OBJ = main.o STARPU.o GUESSP.o PREFUN.o SAMPLE.o 
EXEC = main.x

%.o:%.cpp 
	$(CMPR) -c $(CFLAGS) $(CPPFLAGS) $<

# Link into an executable
main: $(OBJ)
	$(CMPR) $(OBJ) -o $(EXEC) 


clean:
	rm -f ./*.o ./*.x ./Error_File ./Output_File
