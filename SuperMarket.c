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

	printf("There are %d listed customers\n", pSuperMarket->numOfCustomers);
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		printCustomer(&pSuperMarket->customers[i]);
	}
	printf("\n\n"); //cosmetic
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
	Product* tempProd = (Product*)malloc(sizeof(Product));
	if (!tempProd) {
		return 0;
	}
	
	scanBarcode(tempProd); //scan barcode to check if exist
	int index = findBarcode(pSuperMarket, tempProd->barcode);
	if (index == -1) { //product doesnt exist
		if (!initProduct(tempProd)) {
			freeProduct(tempProd);
			return 0;
		}
		if (!addProductToArray(pSuperMarket, tempProd)) {
			freeProduct(tempProd);
		}
	}
	else {
		scanProductStock(&pSuperMarket->products[index],1); //update stock
	}

	return 1;	
}

//allocates or extends products array by 1
int reallocProductsArray(SuperMarket* pSuperMarket) {
	
	if (!pSuperMarket->products) { //if NULL
		pSuperMarket->products = (Product*)malloc(sizeof(Product));

		if (!pSuperMarket->products) { //check if not allocated
			return 0;
		}
	}
	
	pSuperMarket->products = (Product*)realloc(pSuperMarket->products , sizeof(Product) * (pSuperMarket->numOfProducts + 1));
	if (!pSuperMarket->products) {
		return 0;
	}
	return 1;
}

//adds a new product to array
int addProductToArray(SuperMarket* pSuperMarket, Product* pProduct) {
		if (!reallocProductsArray(pSuperMarket)) { //allocates product array
			return 0;
		}
		pSuperMarket->products[pSuperMarket->numOfProducts++] = *pProduct; //insert product to array
		return 1;
}

//returns index of product if the barcode exists, returns -1 if doesnt exist in productArray
int findBarcode(SuperMarket* pSuperMarket, const char* barcode) {
	if (!pSuperMarket->products) { //no products at all!
		return -1;
	}
	
	for (int i = 0; i < pSuperMarket->numOfProducts; i++) {
		if (!strcmp(barcode, pSuperMarket->products[i].barcode)) {
			return i; //return index of product
		}
	}
	return -1;
}

//add customer to supermarket
int addCustomer(SuperMarket* pSuperMarket) {
	Customer* tempCustomer = (Customer*)malloc(sizeof(Customer));
	initCustomer(tempCustomer);
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		if (!strcmp(pSuperMarket->customers[i].name, tempCustomer->name)) {
			printf("Customer already exist, cannot add him/her again!\n\n");
			freeCustomer(tempCustomer);
			return 0;
		}
	}
	if (!pSuperMarket->customers) {
		pSuperMarket->customers = (Customer*)malloc(sizeof(Customer));
	}
	else {
		pSuperMarket->customers = (Customer*)realloc(pSuperMarket->customers, sizeof(Customer) * (pSuperMarket->numOfCustomers + 1));
	}
	if (!pSuperMarket->customers) { //if couldnt allocate memmory
		return 0;
	}
	pSuperMarket->customers[pSuperMarket->numOfCustomers++] = *tempCustomer;
	return 1;
}