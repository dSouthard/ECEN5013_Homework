# ECEN 5013 Spring 2016
# Diana Southard
# Project Makefile
# Version 1: Project 1

# Name of executable
EXE=project

# Run natively on BB or host PC
# Determine which environment this is being run on by checking
# environmental variables: currently running OS
OS := $(shell uname -m)
ARM = arm-linux-gnueabi

ifeq ($(OS), armv7l)
	# Running on the BeagleBone, use its values
	CC 		= $(ARM)-gcc
	SIZE 	= $(ARM)-size
	OBJDUMP = $(ARM)-objdump
else
	# Running on PC, use default values
	CC 		= gcc
	SIZE 	= size
	OBJDUMP = objdump
endif


# Extra flags to give to compiler/linker
CFLAGS = -03 -Wall
LDFLAGS = -lm

# Directory Macros
ROOT_DIR := $(shell pwd)
OBJ_DIR = $(ROOT_DIR)/obj
ASM_DIR = $(ROOT_DIR)/asm
MAP_DIR = $(ROOT_DIR)/map


# Add a second file to your make system,sources.mk. This file needs to include
# a list of the source files and include paths that need to be used for your
# build system.
include sources.mk

# Find all sources
SRCS = $(wildcard *.c)

# Find all objects
OBJS = $(wildcard *.o)

# project
project: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
# Individual targets with header files
memory.c: memory.h
project_1.c: project_1.h

# %.o
# This should be able to individually compile (not link) any single
# object file by specifying the object file you wish to compile
%.o: %.c %.h
	$(CC) –c $(OBJ_DIR)/$@ $< $(CFLAGS) 

# compile-all
# This should compile your object files but DO NOT link
.PHONY: compile-all
compile-all: 
	$(OBJS)


# Build
# This should compile all object files and link
.PHONY: build
build: $(OBJS)
	project

# Upload
# This should be able to take an executable (generate or already generated) 
# and copy it over to a release directory on the beagle bone using scp.
# Connection information regarding the beagle bone will need to be stored
# somehow. This can be done use the makefile directly or calling an external
# bash script to scp the file over
.PHONY: upload
upload: 
	build
	scp $(EXE) root@192.168.7.2:/home/debian/bin/release/


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
	
# OBJ_DIR
# If object directory has not yet been created, auto-generate it
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# MAP_DIR
# If object directory has not yet been created, auto-generate it
$(OBJ_DIR):
	mkdir -p $(MAP_DIR)


#  Clean
# This should remove all compiled objects, executables, and build output files
.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ_DIR) 



