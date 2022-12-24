#pragma once
#include <stdio.h>
#include <stdlib.h>

#define PRODUCT_NAME_LEN 20
#define BARCODE_LEN 7

typedef enum {Shelf, Frozen, Fridge,FruiyVegtable} ProductType;


typedef struct {
	char name[PRODUCT_NAME_LEN+1];
	char barcode[BARCODE_LEN + 1]; //CAPS and digits only!!!
	ProductType type;
	float price;
	int stock;
}Product;


void initProduct();
void printProduct(const Product* pProduct);
void freeProduct(Product* pProduct);