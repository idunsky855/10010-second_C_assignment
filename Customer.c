#include <stdio.h>
#include <stdlib.h>
#include "Customer.h"

#define MAX_STR_LEN 255


int initCustomer(Customer* pCustomer) {

	pCustomer->name = createDynamicStr("Please enter customer's name: ");
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
		printf("Shopping cart is empty!\n");
		return;
	}
	printf("Doing shopping now!!!\n");
}


char* createDynamicStr(const char* msg) {
	char* str;
	char temp[MAX_STR_LEN];
	printf(msg);

	fgets(temp, MAX_STR_LEN, stdin);
	int size = strlen(temp);
	str = (char*)malloc((size + 1) * sizeof(char));
	if (!str)
		return NULL;
	strcpy(str, temp);
	str[size - 1] = '\0';
	return str;
}