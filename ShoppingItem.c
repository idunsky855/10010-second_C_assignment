#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Product.h"
#include "ShoppingItem.h"


int initShoppingItem(ShoppingItem* pShoppingItem, const char* barcode, const float price, int count) {
	char temp[TEMP_BARCODE_LEN];
	strcpy(pShoppingItem->barcode, barcode);
	pShoppingItem->price = price;
	pShoppingItem->count = count;
	return 1;
}

void printShoppingItem(const ShoppingItem* pShoppingItem) {
	////////////////////////////////////////////////
}

void freeShoppingItem(ShoppingItem* pShoppingItem) {
	free(pShoppingItem);
}

void updateShoppingItem(ShoppingItem* pShoppingItem, int count) {
	pShoppingItem->count += count;
}