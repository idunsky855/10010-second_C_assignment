#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ShoppingCart.h"

typedef struct {
	char* name;
	ShoppingCart* pCart;
} Customer;

int initCustomer(Customer* pCustomer);
void freeCustomer(Customer* pCustomer);
void printCustomer(const Customer* pCustomer);
