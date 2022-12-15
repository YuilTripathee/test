#include <conio.h>   // C standard Console Input/Output library
#include <stdio.h>   // C standard IO library
#include <stdlib.h>  // standard library
#include <string.h>  // string manipulation utility

#ifndef UTIL_H
#define UTIL_H

int getID();
// int billFileNo();
int getBalance();
int insertBalance(int value);
// time utility functions
char* getDate();
char* getTime();
char* getYear();
char* getMonth();
char* getDay();

#endif

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

//
// local storage information about the files
//
// this is where all the product information are stored
char file_product[12];

// this is where all the invoice are stored
char file_bill[9];

int total;

#endif /* UTIL_H */
