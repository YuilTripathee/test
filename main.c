// Online Inventory Management System
// CPE100 - Computer Programming

#include "app/util/util.h"

#include "app/invoice.h"
#include "app/model.h"
#include "app/product.h"

int main() {
  FILE* fp;  // file pointer
  int choice;

  // this clear screen is for UNIX-like system (Linux, macOS)
  system("clear");

  while (1) {
    // clear screen (cls command is for command promt type windows)
    system("cls");

    printf(
        "==============================================================\n\n");

    printf("\t\t Welcome to Shop Management System\n\n");

    printf(
        "==============================================================\n\n");

    printf("1. Manage Product\n\n");
    printf("2. Purchase Product\n\n");

    printf("3. Sales Record\n\n");

    printf("0. Exit\n\n");

    printf(
        "==============================================================\n\n");
    printf("Balance: %d\n", getBalance());
    printf("\nPlease enter your Choice:");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        manageProduct();
        break;

      case 2:
        purchaseProduct();
        break;

      case 3:
        generateBill();
        break;

      case 0:
        exit(0);
    }

    getch();
  }

  return 0;
}

// int billFileNo()
//{
//	FILE *fp;
//	int value=0;
//	fp=fopen("billno.txt","r");
//
//	if(fp==NULL)
//	{
//		fp=fopen("billnp.txt","w");
//		fprintf(fp,"%d",0);
//		fclose(fp);
//		fp=fopen("billno.txt","r");
//	}
//	fscanf(fp,"%d",&value);
//
//	fclose(fp);
//
//	fp=fopen("billno.txt","w");
//	fprintf(fp,"%d",value+1);
//	fclose(fp);
//
//	return value+1;
// }
