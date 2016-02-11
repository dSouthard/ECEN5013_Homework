# Homework 2, ECEN 5013 Spring 2016
# Diana Southard

CC = gcc
CFLAGS = -Wall

main: main.o memory.o project_1.o
	$(CC) $(CFLAGS) -o main memory.o project_1.o main.o
	
project_1.o: project_1.c project_1.h
memory.o: memory.c memory.h
main.o: main.c


