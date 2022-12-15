# Project: Library Management System
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe
CC       = gcc.exe
WINDRES  = windres.exe
BIN      = "app.exe"
RM       = rm -f
OBJ = util/util.o


hello:
	echo "Hello, World"

build:
	gcc -o $(BIN) main.c app/model.h app/invoice.c app/product.c app/util/util.c

clean:
	$(RM) $(OBJ) $(BIN)