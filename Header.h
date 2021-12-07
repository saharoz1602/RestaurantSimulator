#ifndef _main
#define _main
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TABLES 15
#define MAX_LEN 100
typedef  enum { FALSE, TRUE } BOOL;
typedef struct Kitchen
{
	int count; // number of the dishes in the manu
	struct Dish* head;
}Kitchen;
typedef struct Dish
{
	char* ProductName;
	int Price;
	int Quantity;
	char Premium;
	struct Dish* next;
}Dish;
typedef struct Order
{
	char* PoductName;
	int Quantity;
	char Premium;
	int price;
	struct Order* next;
	struct Order* prev;
}Order;
typedef struct Table
{
	int TableNumber;
	int bill;
	Order* head;

}Table;
void CreateProducts(Kitchen*);
void Error_Msg(char*);
void AddItems(int, char*, Kitchen*);
void OrderItem(int, char*, int, Table*, Kitchen*);
void DeleteKitchen(Kitchen*);
void Deletetable(Table*);
BOOL Namecheck(Order*, char*);
void RemoveItem(int TableNumber, char* ProductName, int Quantity, Table* tab);
void RemoveTable(int, Table*);
void initTable(Table*, int);
#endif
