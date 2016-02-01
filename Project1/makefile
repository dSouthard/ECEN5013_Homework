# Project 1
EXE=project

# Define compiler/linker
CC = gcc
LD = ld

# Extra flags to give to compiler/linker
CFLAGS = -03 -Wall
LDFLAGS = 

# Dependencies prerequisites and recipes
main.o: main.c
	$(CC) -c main.c
memory.o: memory.c memory.h
	$(CC) -c memory.c
project_1.o: project_1.c project_1.h
	$(CC) -c project_1.c

# %.o
# This should be able to individually compile (not link) any single
# object file by specifying the object file you wish to compile
# %.o:

# Compile-All
# This shuld compile your object files but DO NOT link
compile-all:
	$(CC) -c $(CFLAGS)

# Build
# This should compile all object files and link

#  Link
project:main.o
	gcc -O3 -o $@ $^

#  Clean
# This should remove all compiled objects, executables, and build output files
clean:
	rm -f $(EXE) *.o *.a *.map *.out *.s *.asm
	
# Upload
# This should be able to take an executable (generate or already generated) 
# and copy it over to a release directory on the beagle bone using scp.
# Connection information regarding the beagle bone will need to be stored
# somehow. This can be done use the makefile directly or calling an external
# bash script to scp the file over


# Asm-file
# You should be able to generate assembly output of any single individual file.
# You can do this by providing a single target name You will need to use the -S
# for the assembly output
