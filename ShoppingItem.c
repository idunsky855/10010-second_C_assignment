#include <stdio.h>
#include <stdlib.h>
#include "Product.h"
#include "ShoppingItem.h"


int initShoppingItem(ShoppingItem* pShoppingItem) {
	char temp[TEMP_BARCODE_LEN];
	getValidBarcode(temp);
	strcpy(pShoppingItem->barcode, temp);
	pShoppingItem->barcode[BARCODE_LEN] = '\0';
	////////////////////////////////////////////////
	return 1;
}

void printShoppingItem(const ShoppingItem* pShoppingItem) {
	////////////////////////////////////////////////
}

void freeShopingItem(ShoppingItem* pShoppingItem) {
	////////////////////////////////////////////////
}