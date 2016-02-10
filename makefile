# Project 1
EXE=project


# Run natively on BB or host PC
# Determine which environment this is being run on by checking
# environmental variables: currently running OS
OS := $(shell uname -m)
ARM = arm-linux-gnueabi

ifeq($(OS), armv7l)
	# Running on the BeagleBone
	CC = $(ARM)-gcc
	SIZE = $(ARM)-size
else
	CC = gcc
	SIZE = size


# Extra flags to give to compiler/linker
CFLAGS = -03 -Wall
LDFLAGS = 


# Add a second file to your make system,sources.mk. This file needs to include
# a list of the source files and include paths that need to be used for your
# build system.
# 
# TODO
include sources.mk


# Directory Macrors
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

# vpath
# Search for targets in other directories
vpath %.h $(INCLUDES)/$(HDR_DIR)
vapth %.o $(INCLUDES)/obj
vpath %.c ../src


# Find all sources
SRCS = $(shell find $(SRC_DIR) -name '*.c')


# Find all objects
OBJS = $(shell find $(OBJ_DIR) -name '*.o')


# Individual targets with header files
memory.c: memory.h
project_1.c: project_1.h


# %.o
# This should be able to individually compile (not link) any single
# object file by specifying the object file you wish to compile
%.o: %.c
	$(CC) –c $(OBJ_DIR)/$@ $< $(CFLAGS) 
	

# OBJ_DIR
# If object directory has not yet been created, auto-generate it
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


# compile-all
# This should compile your object files but DO NOT link
.PHONY: compile-all
compile-all:
	$(OBJS)


# Build
# This should compile all object files and link
.PHONY: build
build:
	compile-all project


# project
project:main.o
	$(CC) -o $@ $^ $(CFLAGS)


# Upload
# This should be able to take an executable (generate or already generated) 
# and copy it over to a release directory on the beagle bone using scp.
# Connection information regarding the beagle bone will need to be stored
# somehow. This can be done use the makefile directly or calling an external
# bash script to scp the file over
.PHONY: upload
upload: 
	build
	scp project root@192.168.7.2:/home/debian/bin/release


# %.asm
# You should be able to generate assembly output of any single individual file.
# You can do this by providing a single target name You will need to use the -S
# for the assembly output
%.asm:%.c
	$(CC) $(CFLAGS) -S -o $(ASM_DIR)/$@ -c $<


# %.S
# You should be able to generate assembly output of any single individual file.
# You can do this by providing a single target name You will need to use the -S
# for the assembly output
%.S:%.c
	$(CC) $(CFLAGS) -S -o $(ASM_DIR)/$@ -c $<


# ASM_DIR
# If assembly directory has not yet been created, auto-generate it
$(ASM_DIR):
	mkdir -p $(ASM_DIR)


#  Clean
# This should remove all compiled objects, executables, and build output files
.PHONY: clean
clean:
	rm -f $(EXE) *.o *.a *.map *.out *.s *.asm



