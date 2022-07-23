S = src
CC = g++
CFLAGS =  -std=c++17 -c
OBJS = \
	$S/ast.o \
	$S/driver.o \
	$S/lexer.o \
	$S/main.o \
	$S/parser.o 

kaleido : $(OBJS)
	$(CC) -o kaleido $(OBJS) -std=c++17



$S/main.o : $S/driver.hpp 
	$(CC) -o $S/main.o $(CFLAGS) $S/main.cpp
$S/driver.o : $S/driver.hpp
	$(CC) -o $S/driver.o $(CFLAGS) $S/driver.cpp
$S/parser.o : $S/parser.hpp
	$(CC) -o $S/parser.o  $(CFLAGS) $S/parser.cpp
$S/lexer.o : $S/lexer.hpp
	$(CC) -o $S/lexer.o $(CFLAGS) $S/lexer.cpp
$S/ast.o : $S/ast.hpp 
	$(CC) -o $S/ast.o $(CFLAGS) $S/ast.cpp



.PHONY : clean 
clean : 
	rm kaleido $(OBJS)
