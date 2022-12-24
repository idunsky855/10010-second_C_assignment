#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"

#define MAX_STR_LEN 255


int initCustomer(Customer* pCustomer) {

	pCustomer->name = createDynamicStr("Please enter customers name : ");
	if (!pCustomer->name)
		return 0;

	pCustomer->pCart = (ShoppingCart*)malloc(sizeof(ShoppingCart));
	if (!pCustomer->pCart) {
		free(pCustomer->name);
		return 0;
	}

	if (!initShoppingCart(pCustomer->pCart)) {
		freeCustomer(pCustomer);
		return 0;
	}

	return 1;
}
void freeCustomer(Customer* pCustomer) {

}
void printCustomer(const Customer* pCustomer) {

}


char* createDynamicStr(const char* msg) {
	char* str;
	char temp[MAX_STR_LEN];
	printf(msg);

	str = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	if (!str)
		return NULL;
	strcpy(str, temp);
	return str;
}