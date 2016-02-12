# ECEN 5013 Spring 2016
# Diana Southard
# Project Makefile
# Version 1: Project 1

# Name of project executable
EXE = project

# Run natively on BB or host PC
# Determine which environment this is being run on by checking
# environmental variables: currently running OS
OS := $(shell uname -m)
ARM = arm-linux-gnueabi

# Directory Macros
ROOT_DIR := $(shell pwd)
OUTPUT_DIR = $(ROOT_DIR)/output

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
CFLAGS = -std=c99 -Wall -g -O0 -fno-builtin -fno-builtin-memcpy -fno-builtin-memmove
# Option to create maps in the output directory
LDFLAGS = -Xlinker -Map=$(OUTPUT_DIR)/$@.map

# BeagleBone Login Macros
BB_LOGIN = root@192.168.7.2
BB_DIR = /home/debian/bin/release

# Add a second file to your make system,sources.mk. This file needs to include
# a list of the source files and include paths that need to be used for your
# build system.
# Only include once
include sources.mk


# Phony targets for all functions
.PHONY: setup clean upload build test

# Make targets
build: compile-all setup
	$(CC) $(LDFLAGS) $(CFLAGS) $(addprefix $(OUTPUT_DIR)/,$(OBJS)) -o $(EXE)
	@echo "project build complete."

compile-all: $(OBJS) setup
	@echo "compile-all complete."

%.o: %.c setup
	$(CC) $(CFLAGS) -c $< -o $(OUTPUT_DIR)/$@
	@echo "Build of $@ complete."

%.S: %.c setup
	$(CC) $(CFLAGS) -S $< -o $(OUTPUT_DIR)/$@
	@echo ".S Build of $@ complete."

%.asm: %.c setup
	$(CC) $(CFLAGS) -S $< -o $(OUTPUT_DIR)/$@
	@echo ".asm Build of $@ complete."

upload: build
	ssh $(SCP_LOGIN) mkdir -p $(SCP_DIR)
	scp $(EXE) $(SCP_LOGIN):$(SCP_DIR)
	@echo "upload of $@ complete."

test: $(TEST_OBJS) setup
	$(CC) $(LDFLAGS) $(CFLAGS) $(TEST_OBJECTS) -o $(OUTPUT_DIR)
	@echo "test build complete."

clean:
	rm -rf $(EXE) $(OUTPUT_DIR)
	
# setup
# If output directory has not yet been created, auto-generate it
setup:
	mkdir -p $(OUTPUT_DIR)
