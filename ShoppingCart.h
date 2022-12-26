#pragma once
#include "ShoppingItem.h"

typedef struct {
	ShoppingItem** items;
	int numOfItems;
}ShoppingCart;



int initShoppingCart(ShoppingCart* pShoppingCart);
void printShoppingCart(const ShoppingCart* pShoppingCart);
void freeShoppingCart(ShoppingCart* pShoppingCart);

