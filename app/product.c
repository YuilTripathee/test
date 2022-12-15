#include <stdio.h>

#include "model.h"
#include "product.h"
#include "util/util.h"

void manageProduct() {
  int choice;
  int back = 0;
  while (1) {
    system("cls");

    printf(
        "==============================================================\n\n");

    printf("\t\t Welcome to Shop Management System\n\n");

    printf(
        "==============================================================\n\n");

    printf("1. Add New Product\n\n");
    printf("2. Restock Available Product\n\n");
    printf("3. Display All Product\n\n");

    printf("0. Back\n\n");

    printf(
        "==============================================================\n\n");
    printf("Balance: %d\n", getBalance());
    printf("\nPlease enter your Choice:");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        addProduct();
        break;

      case 2:
        restock();
        break;

      case 3:
        displayAllProduct();
        printf("\nPress Any Key to Exit>>");
        break;

      case 0:
        back = 1;
        break;
    }

    if (back == 1) {
      break;
    } else {
      getch();
    }
  }
}

void addProduct() {
  FILE *fp, *fp1;
  struct Bill t1;
  struct Product t2;

  fp = fopen(file_product, "ab");

  t2.ID = getID();

  printf("\nEnter product name:");
  scanf("%s", t2.name);
  printf("\nEnter product cost:");
  scanf("%d", &t2.cost);
  printf("\nEnter product price:");
  scanf("%d", &t2.price);
  printf("\nEnter product quantity:");
  scanf("%d", &t2.qty);

  // printf("\nTesting: %d\n",-1*t2.cost*t2.qty);
  insertBalance(-1 * t2.cost * t2.qty);

  fwrite(&t2, sizeof(t2), 1, fp);
  fclose(fp);

  fp1 = fopen(file_bill, "ab");

  t1.PurchaseID = t2.ID;
  strcpy(t1.P_Name, t2.name);
  t1.P_Quantity = t2.qty;
  t1.P_Price = -1 * t2.cost * t2.qty;

  strcpy(t1.P_Date, getDate());
  strcpy(t1.P_Time, getTime());
  strcpy(t1.P_Day, getDay());
  strcpy(t1.P_Month, getMonth());
  strcpy(t1.P_Year, getYear());

  fwrite(&t1, sizeof(t1), 1, fp1);

  fclose(fp1);
}

void restock()  // new function
{
  int id, qty;
  system("cls");
  printf("==============================================================\n\n");

  printf("\t\t Welcome to Shop Management System\n\n");

  printf("==============================================================\n\n");

  while (1) {
    FILE* fp;
    struct Bill t1;
    struct Product t2;

    displayAllProduct();
    fflush(stdin);
    // Less Y/N uses 0 to exit instead
    printf("\n\n\nEnter Product ID to Restock(0=Exit):");
    scanf("%d", &id);
    if (id == 0) {
      break;
    }
    fp = fopen(file_product, "ab");
    fp = fopen(file_bill, "ab");

    t2 = findProduct(id);
    // restock in 1 go
    printf("\n\nEnter Product Quantity:");
    scanf("%d", &qty);
    if (t2.qty + qty < 0) {
      printf("\n!!Invalid Quantity!!");
      getch();
      continue;
    }
    insertBalance(-1 * t2.cost * qty);
    updateProduct(t2.ID, t2.qty + qty);

    t1.PurchaseID = t2.ID;
    strcpy(t1.P_Name, t2.name);
    t1.P_Quantity = qty;
    t1.P_Price = -1 * t2.cost * qty;

    strcpy(t1.P_Time, getTime());
    strcpy(t1.P_Date, getDate());
    strcpy(t1.P_Day, getDay());
    strcpy(t1.P_Month, getMonth());
    strcpy(t1.P_Year, getYear());

    fwrite(&t1, sizeof(t1), 1, fp);

    fflush(stdin);
    // getch();
    fclose(fp);
  }
}

void displayAllProduct() {
  FILE* fp;
  struct Product t;
  int id, found = 0;

  system("cls");

  fp = fopen(file_product, "rb");

  printf("==============================================================\n\n");
  printf("\t\t Product Details \n\n");
  printf("==============================================================\n\n");

  printf("   ID\tName\t\t Cost\tQuantity\tPrice\n\n");

  while (1) {
    fread(&t, sizeof(t), 1, fp);

    if (feof(fp) || fp == NULL) {
      break;
    }

    printf("  %3d\t", t.ID);
    printf("%-15s\t", t.name);
    printf("%5d\t", t.cost);
    printf("%7d\t", t.qty);
    printf("%13d\n", t.price);
  }
  printf("==============================================================\n\n");
  printf("Balance: %d\n", getBalance());
  fclose(fp);
}

struct Product findProduct(int id) {
  FILE* fp;
  struct Product t;

  fp = fopen(file_product, "rb");

  while (1) {
    fread(&t, sizeof(t), 1, fp);

    if (feof(fp)) {
      printf("This Product Does Not Exist");
      break;
    }

    if (t.ID == id) {
      updateProduct(id, t.qty);  // change minus 1 when purchase to line 261
      break;
    }
  }
  fclose(fp);
  return t;
}

void updateProduct(int id, int qty) {
  FILE *fp, *fp1;
  struct Product t, t1;
  int found = 0;

  fp = fopen(file_product, "rb");
  fp1 = fopen("temp.dat", "wb");

  while (1) {
    fread(&t, sizeof(t), 1, fp);

    if (feof(fp)) {
      break;
    }
    if (t.ID == id) {
      found = 1;
      t.qty = qty;
      fwrite(&t, sizeof(t), 1, fp1);
    } else {
      fwrite(&t, sizeof(t), 1, fp1);
    }
  }
  fclose(fp);
  fclose(fp1);

  if (found == 0) {
    printf("Sorry No Record Found\n\n");
  } else {
    fp = fopen(file_product, "wb");
    fp1 = fopen("temp.dat", "rb");

    while (1) {
      fread(&t, sizeof(t), 1, fp1);

      if (feof(fp1)) {
        break;
      }
      fwrite(&t, sizeof(t), 1, fp);
    }
  }
  fclose(fp);
  fclose(fp1);
}
