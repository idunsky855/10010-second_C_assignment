#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"

#define MAX_STR_LEN 255


int initCustomer(Customer* pCustomer) {

	pCustomer->name = createDynamicStr("Please enter customers name: ");
	if (!pCustomer->name)
		return 0;
	pCustomer->pCart = NULL; //Empty cart
	
	return 1;
}

void freeCustomer(Customer* pCustomer) {
	free(pCustomer->name);
	if (!pCustomer->pCart) {
		free(pCustomer->pCart);
	}
	free(pCustomer);
}



void printCustomer(const Customer* pCustomer) {
	printf("Customer's name: %s", pCustomer->name);
	printf("\t\t");
	if (!pCustomer->pCart) {
		printf("Shopping cart is empty!\n\n");
		return;
	}
	printf("Doing shopping now!!!");
}


char* createDynamicStr(const char* msg) {
	char* str;
	char temp[MAX_STR_LEN];
	printf(msg);

	fgets(temp, MAX_STR_LEN, stdin);
	str = (char*)malloc((strlen(temp) + 1) * sizeof(char));
	if (!str)
		return NULL;
	strcpy(str, temp);
	return str;
}