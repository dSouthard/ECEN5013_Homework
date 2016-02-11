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
# - obj/
# 	- *.o
# - asm
# 	- *.asm
# - map
# 	- *.map
# $(EXE)

ifndef _SOURCES_MK_
	SOURCES_MK = sources

PROJECT1 = $(ROOT_DIR)/project_1
INC_DIR = inc
SRC_DIR = src

# vpath
# Search for targets in other directories
vpath %.h $(PROJECT1)/$(INC_DIR)
vpath %.c $(PROJECT1)/$(SRC_DIR)
vpath %.o $(OBJ_DIR)

endif
