#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	printAllProducts(pSuperMarket);
	printf("There are %d listed customers\n", pSuperMarket->numOfCustomers);
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		printCustomer(&pSuperMarket->customers[i]);
	}
	printf("\n\n"); //cosmetic
}


void printAllProducts(const SuperMarket* pSuperMarket) {
	printf("\nThere are %d products\n", pSuperMarket->numOfProducts);
	printf("%-25s%-15s%-20s%-10s%-4s\n", "Name", "Barcode", "Type", "Price", "Count in stock");
	for (int i = 0; i < NUM_UNDERSCORES; i++) {//cosmetic
		printf("_");
	}
	printf("\n"); //cosmetic

	for (int i = 0; i < pSuperMarket->numOfProducts; i++) {
		printProduct(&pSuperMarket->products[i]);
	}
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
	if (!tempCustomer) {
		return 0;
	}
	initCustomer(tempCustomer);
	if (getCustomerIndex(pSuperMarket, tempCustomer->name) != -1) {
		printf("Customer already exist, cannot add him/her again!\n\n");
		freeCustomer(tempCustomer);
		return 0;
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

//print product by type 
void printProdByType(SuperMarket* pSuperMarket) {
	if (!pSuperMarket->numOfProducts) {
		printf("\nThere are no products in the market!!\n\n");
		return;
	}
	int count = 0;
	Product pProd;
	scanProductType(&pProd);
	for (int i = 0; i < pSuperMarket->numOfProducts; i++) {
		if (pProd.type == pSuperMarket->products[i].type) {
			printProduct(&pSuperMarket->products[i]);
			count++;
		}
	}
	if (count == 0) {
		printf("\nThere are no product of this type in the market\n\n");
	}
}

void printShoppingCartFromSuperMarket(SuperMarket* pSuperMarket) {
	if (!pSuperMarket->customers) {
		printf("There are no registered customers!");
		return;
	}
	if (!pSuperMarket->products) {
		printf("There are no products in market!");
	}
	printf("There are %d listed customers:\n",pSuperMarket->numOfCustomers);
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		printCustomer(&pSuperMarket->customers[i]);
	}
	char* tempName = createDynamicStr("Who is shopping? Enter the name:\n");
	int index = getCustomerIndex(pSuperMarket, tempName);
	if (index == -1) {
		printf("no such customer!");
		free(tempName);
		return;
	}
	printCustomerShoppingCart(&pSuperMarket->customers[index]);
}

//returns index of customer if name is in the array, else -1 
int getCustomerIndex(SuperMarket* pSuperMarket,const char* name) {
	if (!pSuperMarket->numOfCustomers) {
		return -1;
	}
	for (int i = 0; i < pSuperMarket->numOfCustomers; i++) {
		if (!strcmp(pSuperMarket->customers[i].name,name)) {
			return i;
		}
	}
	return -1;
	
}