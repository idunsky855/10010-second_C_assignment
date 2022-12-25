#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Product.h"



int initProduct(Product* pProduct) {
	if (!pProduct) return 0; //check if pProduct is NULL
	
	scanBarcode(pProduct);
	scanProductName(pProduct);
	scanProductType();
	return 1;
}

//scans valid barcode for product
void scanBarcode(Product* pProduct) {
	char temp[TEMP_BARCODE_LEN];
	int numOfDigits;
	do {
		printf("\nEnter product barcode Code should be of 7 length exactly\nUPPER CASE letter and digits\nMust have 3 to 5 digits\nFirst and last chars must be UPPER CASE letter\nFor example A12B40C\n\n");
		fgets(temp,TEMP_BARCODE_LEN,stdin);
		
		numOfDigits = countDigits(temp); // count of digits in the barcode
		if (strlen(temp) != BARCODE_LEN) {// barcode is not 7 chars
			printf("Code should be of 7 length exactly");
		}
		else if (countLowerCaseLetters(temp)) { // there are lower case letters in barcode
			printf("Code cannot contain lower case letters!");
		}
		else if (!isupper(temp[0]) || !isupper(temp[BARCODE_LEN-1])){ //first and last chars are not UPPER CASE
			printf("First and last chars must be UPPER CASE letters!!");
		}
		else if (numOfDigits < 3 ||numOfDigits > 5 ) { //the are not 3-5 digits in barcode
			printf("Must have 3 to 5 digits!");
		}
		else {
			break; //means that the barcode is valid!
		}
	} while (1);

	strcpy(pProduct->barcode, temp);
}

//returns the amout of lower case letters in string
int countLowerCaseLetters(const char* str) {
	int count=0;
	int size = strlen(str);
	for (int i = 0; i < size; i++) {
		if (islower(str[i])){
			count++;
		}
	}
	return count;
}

//returns the amount of digits in a string
int countDigits(const char* str) {
	int count = 0;
	int size = strlen(str);
	for (int i = 0; i < size; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			count++;
		}
	}
	return count;
}

void scanProductName(Product* pProduct) {
	printf("Please enter product's name:");
	fgets(pProduct->name,PRODUCT_NAME_LEN,stdin);// assuming the products name can contain numbers
}