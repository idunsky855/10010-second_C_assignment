#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char* street;
	char* city;
	char* houseNumber;
}Address;


void initAddress(Address* pAddress);
void printAddress(const Address* pAddress);
void freeAddress(Address* pAddress);

