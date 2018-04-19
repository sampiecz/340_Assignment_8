#
# PROGRAM: Assign 8   
# PROGRAMMER: Samuel Piecz 
# LOGON ID: Z1732715 
# DATE DUE: 04/04/18 
#
# Compiler variables
CCFLAGS = -ansi -Wall -std=c++11

# Rule to link object code files to create executable file
assignment8: assignment8.o
	g++ $(CCFLAGS) -o assignment8.exe assignment8.o

# Rule to compile source code file to object code
assignment8.o: assignment8.cc
	g++ $(CCFLAGS) -c assignment8.cc

# Pseudo-target to remove object code and executable files
clean:
	-rm -f *.o assignment8.exe
