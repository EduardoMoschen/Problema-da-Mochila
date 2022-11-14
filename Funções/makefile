CC=gcc

CFLAGS= -c -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow 

all : main

main : funcoes.o main.o
	$(CC) funcoes.o main.o -o main -lm

main.o : main.c
	$(CC) $(CFLAGS) main.c -lm

funcoes.o : funcoes.c funcoes.h
	$(CC) $(CFLAGS) funcoes.c -lm

clean : 
	rm *.o main