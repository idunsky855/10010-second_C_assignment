#include <stdio.h>
#include <stdlib.h>
#include "ShoppingCart.h"


int initShoppingCart(ShoppingCart* pShoppingCart) {
	pShoppingCart->items = (ShoppingItem**)malloc(sizeof(ShoppingItem*));
	if (!pShoppingCart->items) {
		return 0;
	}
	pShoppingCart->numOfItems = 0;
	return 1;
}

void printShoppingCart(const ShoppingCart* pShoppingCart) {
		float bill = 0;
	if (!pShoppingCart) {
		printf("Shopping cart is empty!");
	}
	else {

		for (int i = 0; i < pShoppingCart->numOfItems; i++) {
			printShoppingItem(pShoppingCart->items[i]);
			bill += (pShoppingCart->items[i]->price) * (pShoppingCart->items[i]->count);
		}
	}
	printf("Total bill:\t%.2f\n", bill);
}

void freeShoppingCart(ShoppingCart* pShoppingCart) {
	for (int i = 0; i < pShoppingCart->numOfItems; i++) {
		freeShoppingItem(pShoppingCart->items[i]);
	}
	free(pShoppingCart);
}

//int reallocShoppingItemArray(ShoppingCart* pShoppingCart);