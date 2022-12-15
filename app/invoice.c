#include "model.h"
#include "product.h"
#include "util/util.h"

void purchaseProduct() {
  char ch1, ch2;
  int id, qty;
  system("cls");
  printf("==============================================================\n\n");

  printf("\t\t Welcome to Shop Management System\n\n");

  printf("==============================================================\n\n");

  while (1) {
    displayAllProduct();
    fflush(stdin);
    // Less Y/N uses 0 to exit instead;
    printf("\n\n\nEnter the Product ID to Purchase(0=Exit):");
    scanf("%d", &id);
    if (id == 0) {
      break;
    }
    FILE* fp;
    struct Bill t1;
    struct Product t2;

    fp = fopen(file_bill, "ab");
    t2 = findProduct(id);

    printf("\n\nEnter Product Quantity:");
    scanf("%d", &qty);

    // added to prevent negative count in stock
    if (t2.qty - qty < 0) {
      printf("\nSorry, Insufficient Product");
      fflush(stdin);
      getch();
      continue;
    }
    // remove desired product qty
    updateProduct(t2.ID, t2.qty - qty);
    insertBalance(t2.price * qty);

    t1.PurchaseID = t2.ID;
    strcpy(t1.P_Name, t2.name);
    t1.P_Quantity = qty;
    t1.P_Price = t2.price * qty;

    strcpy(t1.P_Time, getTime());
    strcpy(t1.P_Date, getDate());
    strcpy(t1.P_Day, getDay());
    strcpy(t1.P_Month, getMonth());
    strcpy(t1.P_Year, getYear());

    fwrite(&t1, sizeof(t1), 1, fp);

    fclose(fp);

    fflush(stdin);
    getch();
  }
}

void generateBill() {
  total = 0;
  FILE *fp, *fp1;
  struct Bill t;
  int id, found = 0;
  char ch, date[20];
  //	int brel=0;
  //	char billname[20];

  system("cls");
  fflush(stdin);
  fp = fopen(file_bill, "rb");

  printf("==============================================================\n\n");
  printf("\t\t Sales Record \n\n");
  printf("==============================================================\n\n");

  printf("Date    \t\tPro-ID\tPro-Name\tPro-Quantity\tPro-Price\n\n");

  while (1) {
    fread(&t, sizeof(t), 1, fp);

    if (feof(fp) || fp == NULL) {
      break;
    }
    printf("%s_%s", t.P_Date, t.P_Time);
    printf("        %3d\t", t.PurchaseID);
    printf("%-10s\t", t.P_Name);
    printf("%8d\t", t.P_Quantity);
    printf("%7d\t\t\t\n", t.P_Price);
    total = total + t.P_Price;
  }
  if (total >= 0) {
    printf("\n\n==========>>>>> [Total : %d Baht] {Status: Profit}\n\n", total);
  } else {
    printf("\n\n==========>>>>> [Total : %d Baht] {Status: Loss}\n\n", total);
  }
  printf("Balance: %d\n\n", getBalance());
  printf("==============================================================\n\n");
  printf("1.Specific Day\n\n");
  printf("2.Specific Month\n\n");
  printf("3.Specific Year\n\n");
  printf("0.Back\n\n");
  printf("==============================================================\n\n");
  printf("Enter Your Choice:");
  scanf("%c", &ch);
  fclose(fp);

  if (ch == '0') {
    return;
  }
  if (ch == '1') {
    fflush(stdin);
    fp = fopen(file_bill, "rb");
    total = 0;
    printf("\n\nEnter Date/Month/Year:");
    scanf("%s", date);
    printf("Date    \t\tPro-ID\tPro-Name\tPro-Quantity\tPro-Price\n\n");
    while (1) {
      fread(&t, sizeof(t), 1, fp);

      if (feof(fp) || fp == NULL) {
        break;
      }
      if (strcmp(date, t.P_Date) == 0) {
        printf("%s_%s", t.P_Date, t.P_Time);
        printf("        %3d\t", t.PurchaseID);
        printf("%-10s\t", t.P_Name);
        printf("%8d\t", t.P_Quantity);
        printf("%7d\t\t\t\n", t.P_Price);
        total = total + t.P_Price;
      }
    }
    printf("\n->Total: %d Baht\n", total);
    fclose(fp);
  }
  if (ch == '2') {
    fflush(stdin);
    char temp[20];

    fp = fopen(file_bill, "rb");
    total = 0;
    printf("\n\nEnter Month/Year:");
    scanf("%s", date);
    printf("Date    \t\tPro-ID\tPro-Name\tPro-Quantity\tPro-Price\n\n");
    while (1) {
      fread(&t, sizeof(t), 1, fp);
      sprintf(temp, "%s/%s", t.P_Month, t.P_Year);
      if (feof(fp) || fp == NULL) {
        break;
      }
      if (strcmp(date, temp) == 0) {
        printf("%s_%s", t.P_Date, t.P_Time);
        printf("        %3d\t", t.PurchaseID);
        printf("%-10s\t", t.P_Name);
        printf("%8d\t", t.P_Quantity);
        printf("%7d\t\t\t\n", t.P_Price);
        total = total + t.P_Price;
      }
    }
    printf("\n->Total: %d Baht\n", total);
    fclose(fp);
  }
  if (ch == '3') {
    fflush(stdin);
    fp = fopen(file_bill, "rb");
    total = 0;
    printf("\n\nEnter Year:");
    scanf("%s", date);
    printf("Date    \t\tPro-ID\tPro-Name\tPro-Quantity\tPro-Price\n\n");
    while (1) {
      fread(&t, sizeof(t), 1, fp);
      if (feof(fp) || fp == NULL) {
        break;
      }
      if (strcmp(date, t.P_Year) == 0) {
        printf("%s_%s", t.P_Date, t.P_Time);
        printf("        %3d\t", t.PurchaseID);
        printf("%-10s\t", t.P_Name);
        printf("%8d\t", t.P_Quantity);
        printf("%7d\t\t\t\n", t.P_Price);
        total = total + t.P_Price;
      }
    }
    printf("\n->Total: %d Baht\n", total);
    fclose(fp);
  }

  //	if(total!=0)
  //	{
  //		fflush(stdin);
  //		printf("\n\n\nDo you want to generate Final Bill [Y/N]:");
  //		scanf("%c",&ch1);
  //
  //		if(ch1=='Y')
  //		{
  //			brel=billFileNo();
  //			sprintf(billname,"%s%d","",brel);
  //			strcat(billname,".dat");
  //
  //			fp=fopen(fbill,"rb");
  //			fp1=fopen(billname,"wb");
  //
  //			while(1)
  //			{
  //				fread(&t,sizeof(t),1,fp);
  //
  //				if(feof(fp))
  //				{
  //					break;
  //				}
  //				fwrite(&t,sizeof(t),1,fp1);
  //			}
  //			fclose(fp);
  //			fclose(fp1);
  //
  //			fp=fopen(fbill,"wb");
  //			fclose(fp);
  //			total=0;
  //		}
  //	}
  //	else
  //	{
  //		printf("\n\n Sorry, no item selected \n\n");
  //	}
}
