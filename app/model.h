#ifndef MODEL_H
#define MODEL_H
// any product that goes into into inventory
struct Product {
  int ID;
  char name[50];
  int price;
  int qty;
  int cost;
};

// invoice information of a single purchase event
struct Bill {
  int PurchaseID;  // purchase ID

  // purchase information
  char P_Name[20];  // purchase name
  int P_Quantity;   // purchase quantity
  int P_Price;      // purchase price

  // time of purchase (just a redundant technique used to mention the purchases)
  char P_Year[20];   // purchase year
  char P_Month[20];  // purchase month
  char P_Day[20];    // purchase day
  char P_Date[20];   // purchase data
  char P_Time[20];   // purchase time
};

#endif /* MODEL_H */