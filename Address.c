#include <stdio.h>
#include <stdlib.h>
#include "Address.h"

#define MAX_STR_SIZE 255

int initAddress(Address* pAddress) {
	printf("Please enter street, number and city\nformat: Street#Number#City\nstreet and city can have spaces in them");
	char str[MAX_STR_SIZE];
	fgets(str,MAX_STR_SIZE,stdin);
	char delimiter = '#';
	
	pAddress->street = strtok(str, delimiter);
	if (!pAddress->street) {
		return 0;
	}

	
	pAddress->houseNumber = strtok(NULL, delimiter);
	if(!pAddress->houseNumber){
		return 0;
	}
	pAddress->city = strtok(NULL, delimiter);
	if (!pAddress->city) {
		return 0;
	}
	
	return 1;
}

void printAddress(const Address * pAddress)	{
}
void freeAddress(Address* pAddress) {


}




