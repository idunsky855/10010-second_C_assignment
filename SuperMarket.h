#pragma once
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


int initSuperMarket(SuperMarket* pSuperMarket);
void printSuperMarket(const SuperMarket* pSuperMarket);
void freeSuperMarket(SuperMarket* pSuperMarket);
int addProductToSuperMarket(SuperMarket* pSuperMarket);
int reallocProductsArray(SuperMarket* pSuperMarket);
int addProductToArray(SuperMarket* pSuperMarket, Product* pProduct);
int findBarcode(SuperMarket* pSuperMarket, const char* barcode);
int addCustomer(SuperMarket* pSuperMarket);
void printProdByType(SuperMarket* pSuperMarket);