#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ShoppingCart.h"
#include "Customer.h"
#include "Product.h"
#include "Address.h"

typedef struct {
	char* name;
	Address address;
	Customer* customers;
	int numOfCustomers;
	Product* products;
	int numOfProducts;
}SuperMarket;


void initSuperMarket();
void printSuperMarket(const SuperMarket* pSuperMarket);
void freeSuperMarket(SuperMarket* pSuperMarket);