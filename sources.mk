# Add a second file to your make system,sources.mk. This file needs to include
# a list of the source files and include paths that need to be used for your
# build system.
# 
# 

# Directory Structure:
# - makefile
# - sources.mk
# - project_xxx/
# 	- inc/
# 		-*.h
# 	-src/
# 		-*.c
# - output/
# 	- *.o
# 	- *.asm
# 	- *.map
# $(EXE)


# Directory Macros
PROJECT_NAME = project1
PROJECT1_DIR = $(ROOT_DIR)/$(PROJECT_NAME)

# Tell compiler where to look for header files
CFLAGS += -I$(PROJECT1_DIR)/inc/
# Add flag to ignore built-in functions that we overrode
CFLAGS += -fno-builtin -fno-builtin-memcpy -fno-builtin-memmove

# vpath to search for source files
vpath %.c $(PROJECT1_DIR)/src

# All objects
OBJS = memory.o project_1.o main.o
TEST_OBJS = memory.o project_1_test.o main_test.o

