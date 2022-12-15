#include <conio.h>   // C standard Console Input/Output library
#include <stdio.h>   // C standard IO library
#include <stdlib.h>  // standard library
#include <string.h>  // string manipulation utility
#include <time.h>    // time utilities (UNIX time)

char file_product[] = {"product.dat"};

// this is where all the invoice are stored
char file_bill[] = {"bill.dat"};

int total = 0;

int getBalance() {
  FILE* fp;
  int balance = 0;
  fp = fopen("balance.txt", "r");

  if (fp == NULL) {
    fp = fopen("balance.txt", "w");
    fprintf(fp, "%d", 10000);
    fclose(fp);
    fp = fopen("balance.txt", "r");
  }

  fscanf(fp, "%d", &balance);

  fclose(fp);

  fp = fopen("balance.txt", "w");

  fprintf(fp, "%d", balance);

  fclose(fp);

  return balance;
}

int getID() {
  FILE* fp;
  int value = 0;

  fp = fopen("prodid.txt", "r");

  if (fp == NULL) {
    fp = fopen("prodid.txt", "w");
    fprintf(fp, "%d", 0);
    fclose(fp);
    fp = fopen("prodid.txt", "r");
  }

  fscanf(fp, "%d", &value);

  fclose(fp);

  fp = fopen("prodid.txt", "w");

  fprintf(fp, "%d", value + 1);

  fclose(fp);

  return value + 1;
}

int insertBalance(int value) {
  FILE* fp;
  int balance = getBalance();
  fp = fopen("balance.txt", "w");
  fprintf(fp, "%d", balance + value);
  fclose(fp);
}

char* getDate() {
  time_t timer;
  static char buffer[26];
  struct tm* tm_info;

  timer = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%d/%m/%Y", tm_info);
  return buffer;
}

char* getDay() {
  time_t timer;
  static char buffer[26];
  struct tm* tm_info;

  timer = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%d", tm_info);
  return buffer;
}

char* getMonth() {
  time_t timer;
  static char buffer[26];
  struct tm* tm_info;

  timer = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%m", tm_info);
  return buffer;
}

char* getYear() {
  time_t timer;
  static char buffer[26];
  struct tm* tm_info;

  timer = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%Y", tm_info);
  return buffer;
}

char* getTime() {
  time_t timer;
  static char buffer[26];
  struct tm* tm_info;

  timer = time(NULL);
  tm_info = localtime(&timer);

  strftime(buffer, 26, "%H:%M:%S", tm_info);
  return buffer;
}
