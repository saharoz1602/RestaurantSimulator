#include "Header.h"
void CreateProducts(Kitchen* Kit)
{
	FILE* in;
	Dish* temp;
	char Tempstr[MAX_LEN] = { '\0' };
	int i;

	Kit->count = 0;
	temp = Kit->head;

	if (!(in = fopen("Manot.txt", "r")))
	{
		DeleteKitchen(Kit);
		Error_Msg("Dishes input Failed!\nCould not open ""Manot"" file.\n");
	}

	if (!(Kit->head = (Dish*)malloc(sizeof(Dish)))) //allocating first node in the kitchen linking list
	{
		DeleteKitchen(Kit);
		fclose(in);
		Error_Msg("Dishes input Failed!\nMemory allocation problem.\n");
	}

	while ((fscanf(in, "%s", Tempstr) != EOF))
	{

		if (!(temp = (Dish*)malloc(sizeof(Dish)))) //allocating 1 node to dish
		{
			fclose(in);
			DeleteKitchen(Kit);
			Error_Msg("Dishes input Failed!\nMemory allocation problem.\n");
		}
		if (!(Kit->head->ProductName = (char*)malloc(sizeof(char) * strlen(Tempstr)))) // allocating productname
		{
			fclose(in);
			DeleteKitchen(Kit);
			Error_Msg("Dishes input Failed!\nMemory allocation problem.\n");
		}
		strcpy(Kit->head->ProductName, Tempstr);
		fscanf(in, "%d %d %c", &Kit->head->Quantity, &Kit->head->Price, &Kit->head->Premium);
		printf("-*-%s added to the kitchen %d times and it costs %d per dish, ", Kit->head->ProductName, Kit->head->Quantity, Kit->head->Price);
		if (Kit->head->Premium == 'Y')
		{
			printf("it also a Premium Dish\n");
			printf("__________________________\n");
		}
		else
		{
			printf("its not a Premium Dish!\n");
			printf("__________________________\n");
		}
		temp->next = Kit->head; // adding the node to the start of the list
		Kit->head = temp;
		Kit->count++;
	}
	Kit->head = Kit->head->next;
	fclose(in);
	printf("\nDishs input succeeded!\n");
}
void Error_Msg(char* str)
{
	printf("\n%s", str);
	exit(1);
}

void AddItems(int Quantity, char* ProductName, Kitchen* kit)
{
	Dish* temp;
	if (Quantity < 0)
	{
		printf("Error!\n Quantity is negative!\n");
		return;
	}
	temp = kit->head;
	while (temp)
	{
		if (!(strcmp(temp->ProductName, ProductName))) // chacking if the name of the dish is in the kitchen
		{
			temp->Quantity += Quantity; //updating element
			printf("Quantity of %s is updated to %d\n", ProductName, temp->Quantity);
			return;
		}
		temp = temp->next;
	}
	printf("Could not find the request Item!\n");
}

void OrderItem(int TableNumber, char* ProductName, int Quantity, Table* tab, Kitchen* kit)
{
	Order* Tabtemp = NULL, * Tabtemp2;
	Kitchen* Kitemp, * Kitemp2;
	Table* temp;
	temp = tab;
	int flag = 1;
	if (TableNumber > TABLES || TableNumber < 1) //input checking
	{
		printf("Table number %d is wrong\n", TableNumber);
		return;
	}
	if (Quantity <= 0)
	{
		printf("Quantity cannot be negative or zero!\n");
		return;
	}
	Kitemp = kit;
	Tabtemp2 = kit->head;
	while (Kitemp->head)
	{
		if (!(strcmp(Kitemp->head->ProductName, ProductName)))
		{
			if (Quantity > Kitemp->head->Quantity) // checking input 
			{

				printf("Not enough dishs in the kitchen!\n");
				return;
			}

			if (!(Namecheck(temp->head, ProductName)))
			{
				if (!(Tabtemp = (Order*)malloc(sizeof(Order)))) //allocating 1 node to the orders list
				{
					Deletetable(tab);
					DeleteKitchen(kit);
					Error_Msg("Allocation Failed!");
				}
				if (!(Tabtemp->PoductName = (char*)malloc(sizeof(char) * (strlen(ProductName) + 1)))) // allocating product name
				{
					free(Tabtemp);
					Deletetable(tab);
					DeleteKitchen(kit);
					Error_Msg("Allocation Failed!\n");
				}
				strcpy(Tabtemp->PoductName, ProductName);  // updating the node
				Tabtemp->price = Kitemp->head->Price;
				Tabtemp->Quantity = Quantity;
				Tabtemp->Premium = Kitemp->head->Premium;
				Kitemp->head->Quantity -= Quantity;
				printf("Table Number %d order %d %s!\n", TableNumber, Tabtemp->Quantity, ProductName);
			}
			else
			{
				while (temp->head)
				{
					if (!(strcmp(temp->head->PoductName, ProductName)))
					{
						temp->head->Quantity += Quantity;
						while (Kitemp->head)
						{
							if (!(strcmp(Kitemp->head->ProductName, ProductName)))
							{
								Kitemp->head->Quantity -= Quantity; //updating kitchen's quantity
							}
							Kitemp->head = Kitemp->head->next;
						}
						return;
					}
				}
			}
		}
		Kitemp->head = Kitemp->head->next;
	}
	Kitemp->head = Tabtemp;
	kit->head = Tabtemp2;
	if (Tabtemp == NULL)
	{
		printf("Cannot find requested dish!\n");
		return;
	}
	if (NULL == tab->head) // in case that the table has no oreders (empty list)
	{
		tab->head = Tabtemp;
		tab->head->next = NULL;
		tab->head->prev = NULL;
		tab->TableNumber = TableNumber;
		return;
	}
	else
	{
		Tabtemp->next = tab->head;
		tab->head->prev = Tabtemp;  //adding to the start of the list
		Tabtemp->prev = NULL;
		tab->head = Tabtemp;
		tab->TableNumber = TableNumber;
		return;
	}
}

BOOL Namecheck(Order* ord, char* name) // boolean function chacking if string in the node and new string are equal
{
	while (ord)
	{
		if (!(strcmp(ord->PoductName, name)))
		{
			return TRUE;
		}
		ord = ord->next;
	}
	return FALSE;
}

void DeleteKitchen(Kitchen* kit) // deleting kitchen list
{
	Dish* temp;
	if (NULL == kit)
		return;
	else
	{
		while (kit->head)
		{
			temp = kit->head;
			kit->head = kit->head->next;
			free(temp->ProductName);
			free(temp);
		}
		free(kit);
		return;
	}
}

void Deletetable(Table* tab) // deleting tabl's list
{
	Order* temp;
	if (NULL == tab)
		return;
	else
	{
		while (tab->head)
		{
			temp = tab->head;
			tab->head = tab->head->next;
			free(temp->PoductName);
			free(temp);
		}
		free(tab);
		return;
	}
}

void RemoveItem(int TableNumber, char* ProductName, int Quantity, Table* tab)
{
	int Qtemp, Ptemp;
	Table* Ttemp;              // Temp for table
	Order* Otemp, * Otemp2, * Otemp3;     // Otemp for order, Otemp2 for erase node in the list, Otemp3 for helping

	Qtemp = tab->TableNumber;
	if (Quantity > 0) // checking input
	{
		if (Quantity > Qtemp)
		{
			printf("%d is more dishs than the table orderd!\nCannot cancel!\n", Quantity);
			return;
		}
	}
	else
	{
		printf("Quentity cannot be negative or 0!\n");
		return;
	}
	Ttemp = tab;
	Otemp = tab->head;
	while (Otemp)
	{
		if (!(strcmp(Otemp->PoductName, ProductName)))
		{
			Ptemp = (Otemp->price) / (Otemp->Quantity); // to calculate 1 dish price
			Otemp->Quantity -= Quantity;
			Otemp->price -= (Ptemp * Quantity);
			printf("Table number %d canceled %s %d times\n", TableNumber, Otemp->PoductName, Quantity);
			if (!(Otemp->Quantity))
			{
				if (NULL == Otemp->prev) // in case the node is the first in the linking list
				{
					tab->head = Otemp->next;
					tab->head->prev = NULL;
					Otemp->next = NULL;
					free(Otemp->PoductName);
					free(Otemp);
				}
				if (NULL == Otemp->next) //  in case the node is the last in the linking list
				{
					free(Otemp->PoductName);
					Otemp2 = Otemp->prev;
					Otemp2->next = NULL;
					Otemp->prev = NULL;
					free(Otemp);
				}
				if (Otemp->next != NULL && Otemp->prev != NULL) // in case the node is not the first or last in the linking list
				{
					Otemp2 = Otemp->prev;
					Otemp3 = Otemp->next;
					Otemp2->next = Otemp3;
					Otemp3->prev = Otemp2;
					free(Otemp->PoductName);
					free(Otemp);
				}
			}
		}
		Otemp = Otemp->next;
	}

}

void RemoveTable(int TableNumber, Table* tab)
{
	Order* Otemp, * Otemp2 = NULL; // temp to Order
	int Btemp = 0, Ptemp = 0; //Temp for the bill initilizing to zero, Ptemp for primium chacking!
	if (!(tab->head))
	{
		printf("Table number %d order nothing at all!\n", TableNumber);
		return;
	}
	Otemp = tab->head;
	while (Otemp)
	{
		Btemp += (Otemp->price) * (Otemp->Quantity); //calculating the bill
		if (Otemp->Premium == 'Y') // checking if there are any premium dishen in the table's list
		{
			Ptemp = 1;
		}
		Otemp = Otemp->next;
	}
	tab->bill = Btemp; // update the table
	if (Ptemp)
	{
		tab->bill *= 1.1; // in case there is at least one premium dish
	}
	Otemp = tab->head;
	printf("Table number %d order include:\n", TableNumber);
	while (Otemp)
	{
		printf("%s %d times\n", Otemp->PoductName, Otemp->Quantity);
		Otemp = Otemp->next;
	}
	printf("The bill of this table is %d\n", tab->bill);
	if (Ptemp)
	{
		printf("This table was premium\n");
	}
	Otemp = tab->head;

	while (tab->head) //delete the table orders list
	{
		free(tab->head->PoductName);
		if (tab->head->next)
		{
			Otemp2 = tab->head->next;
			if (Otemp2)
			{
				Otemp2->prev = NULL;
				tab->head->next = NULL;
			}
		}
		free(tab->head);
		tab->head = Otemp2;

	}

}

void initTable(Table* tab, int Tablenumber) //initilizing table to NULL and bill to 0 
{
	tab->head = NULL;
	tab->TableNumber = Tablenumber;
	tab->bill = 0;
}