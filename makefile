# Select compiler
CMPR = g++

OBJDIR = ./obj/

CPPFLAGS=$(ARG)
CPPFLAGS +=  

CPP = 
CFLAGS = -std=c++17 -Wall

OBJ = main.o STARPU.o GUESSP.o PREFUN.o SAMPLE.o 
EXEC = main.x

OBJS = $(addprefix $(OBJDIR), $(OBJ))

$(addprefix ./obj/, %.o):%.cpp 
	$(CMPR) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# Link into an executable
main: $(OBJS)
	$(CMPR) $(OBJS) -o $(EXEC) 


clean:
	rm -f ./obj/*.o 
	rm -f ./*.x 
	rm -f ./data/*.dat
