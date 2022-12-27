#include <stdio.h>
#include <stdlib.h>
#include "SuperMarket.h"

#define NUM_UNDERSCORES 74 //cosmetic

int initSuperMarket(SuperMarket* pSuperMarket) {
	pSuperMarket->name = createDynamicStr("Please enter market's name:\n");
	if (!pSuperMarket->name)
		return 0;
	
	if (!initAddress(&pSuperMarket->address)) {
		free(pSuperMarket->name);
		return 0;
	}

	pSuperMarket->customers = NULL;
	pSuperMarket->numOfCustomers = 0;
	pSuperMarket->products = NULL;
	pSuperMarket->numOfProducts = 0;
	
	return 1;
}


void printSuperMarket(const SuperMarket* pSuperMarket) {
	printf("Super Market name: %s\nAddress:", pSuperMarket->name);
	printAddress(&pSuperMarket->address);
	printf("\nThere are %d products\n", pSuperMarket->numOfProducts);
	printf("%-25s%-15s%-20s%-10s%-4s\n", "Name", "Barcode", "Type", "Price", "Count in stock");
	
	for (int i = 0 ; i < NUM_UNDERSCORES ; i++) {//cosmetic
		printf("_");
	}
	printf("\n"); //cosmetic

	for (int i = 0 ; i < pSuperMarket->numOfProducts ; i++ ) {
		printProduct(&pSuperMarket->products[i]);
	}

	printf("There are %d listed customers", pSuperMarket->numOfCustomers);
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		printCustomer(&pSuperMarket->customers[i]);
	}
	printf("\n"); //cosmetic
}

void freeSuperMarket(SuperMarket* pSuperMarket) {
	free(&pSuperMarket->name);
	freeAddress(&pSuperMarket->address);
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		freeCustomer(&pSuperMarket->customers[i]);
	}
	for (int i = 0; i < pSuperMarket->numOfProducts; i++) {
		freeProduct(&pSuperMarket->products[i]);
	}
	free(pSuperMarket);
}

int addProductToSuperMarket(SuperMarket* pSuperMarket) {
	if (!reallocProductsArray(pSuperMarket)) { //allocates product array
		return 0;
	}

	Product* tempProd = (Product*)malloc(sizeof(Product));
	if (!tempProd) {
		return 0;
	}

	if(!initProduct(tempProd)){
		return 0;
	}

	return 1;	
}

//allocates or extends products array by 1
int reallocProductsArray(SuperMarket* pSuperMarket) {
	if (!pSuperMarket->products) {
		pSuperMarket->products = (Product*)malloc(sizeof(Product));
		if (!pSuperMarket->products) { //check if not allocated
			return 0;
		}
	}
	
	Product* pTemp = (Product*)relloc(sizeof(Product) * (pSuperMarket->numOfProducts + 1));
	if (!pTemp) {
			return 0;
	}
	pSuperMarket->products = pTemp;
	return 1;
}

