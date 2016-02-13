# Makefile Instructions

ECEN 5013 Spring 2016

Diana Southard

###**Instruction for compiling with make**

**Makefile Targets**
The makefile supports the following targets:
* make build
* make %.o
* make compile-all
* make %.asm
* make upload
* make clean

These operations are explained below.

```
**make build**
```

- This will compile all object files and links. All output files will appear in a new directory labeled *output* with the exception of the executable **project** which will remain in the root directory.


```
**make %.o**
```

- This will allow to individually compile without linking any single object specified.

```
**make compile-all**
```

- This will compile all objects without linking them.


```
**make %.asm** OR **make %.S**
```

- This will generate the assemply output of any single file.

```
**make upload**
```

- This will take an executable and copy it over to a release directory on the BeagleBone using scp. Connection information regarding the BeagleBone is stored in the Makefile using a macro.


```
**make clean**
```
- This will remove all compiled objects, executables, and build output files. It will also remove the output directory, if created.


###Compiler/Linker Flag Defaults:

**CFLAGS**
```
-O0 						// This level turns off optimization entirely
-g 							// add debug info to program, default
-Wall 						// enable warnings, default
-std=c99					// Determines c99 Standard as the language
-I$(PROJECT1_DIR)/inc/		// Includes header file for compiler
-fno-builtin 				// Directs compiler to ignore built-in functions
-fno-builtin-memcpy			// Directs compiler to ignore built-in memcpy function
-fno-builtin-memmove		// Directs compiler to ignore built-in memmove function
```

**LDFLAGS**
```
-Xlinker -Map=$(OUTPUT_DIR)/$@.map	 // Enables linker maps
```
###**Supported Architectures:**
```
OS = armv7l 				// BeagleBone Black
OS = x86					// Linux/Ubuntu (Native PC)
```

## Supported GNU Utilities
```
DUMP_REQUEST = 1 			// Set to 1 to display object's summary information from the section headers, 0 otherwise
SIZE_REQUEST = 1 			// Set to 1 to enable size information, 0 otherwise
```
