#ifndef PRODUCT_H
#define PRODUCT_H

#include "model.h"
#include "util/util.h"

// product management functions
void manageProduct();
void addProduct();
void restock();
void displayAllProduct();
struct Product findProduct(int id);
void updateProduct(int id, int qty);

#endif
