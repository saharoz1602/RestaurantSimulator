#include "Header.h"

void main()
{
	Kitchen* Kit;
	Dish* temp;
	Table* tabs;
	int i, n, x, y, select;
	char str[MAX_LEN];
	FILE* F;

	if (!(tabs = (Table*)malloc(sizeof(struct Table) * TABLES)))
	{
		Error_Msg("Allocation Failed!\n");
	}//allocat TABLES (15)
	for (i = 0; i < TABLES; i++)//init tabeles
	{
		initTable((tabs + i), i + 1);
	}
	if (!(Kit = (Kitchen*)malloc(sizeof(Kitchen))))
	{
		free(tabs);
		Error_Msg("Allocation failed!\n");
	}//alocate kitchen
	F = fopen("instructions.txt", "rt");
	if (!(F)) //in case that to file opening failed
	{
		free(Kit);
		free(tabs);
		Error_Msg("Could not open the file\n");
	}
	printf("Welcome to our restaurant!\nThe restaurant function is:\n1.Recived the dishs to kitchen\n2.Adding items to the current dishs in the kitchen\n3.Order dishs to the tables\n4.Cancel order items\n5.Closing the table and cacaulate the bill\n\nPlease press '0' to continue.\n\n");
	scanf("%d", &select);
	if (select != 0) // in case that the input is not 0 
	{
		while (select != 0)
		{
			printf("You didnt choose '0',please try again\n");
			scanf("%d", &select);
		}
	}
	while (((fscanf(F, "%d", &n) != EOF)) || select != 0) //run until finishing reading the text in the file 
	{
		switch (n)
		{
		case 1:
			CreateProducts(Kit);
			temp = Kit->head;
			for (i = 0; i < (Kit->count) - 1; i++)
			{
				temp = temp->next;
			}//initilize last node->next to NULL
			temp->next = NULL;
			break;
		case 2:
			fscanf(F, "%s %d", str, &x);
			AddItems(x, str, Kit);
			break;
		case 3:
			fscanf(F, "%d %s %d", &x, str, &y);
			OrderItem(x, str, y, &tabs[x - 1], Kit);
			break;
		case 4:
			fscanf(F, "%d %s %d", &x, str, &y);
			RemoveItem(x, str, y, &tabs[x - 1]);
			break;
		case 5:
			fscanf(F, "%d", &x);
			RemoveTable(x, &tabs[x - 1]);
			break;
		}
		printf("\nPlease press '0' to continue.\n");
		scanf("%d", &select);
		if (select != 0)
		{
			while (select != 0)
			{
				printf("You didnt choose '0',please try again\n");
				scanf("%d", &select);
			}
		}
	}
	DeleteKitchen(Kit);
	Deletetable(tabs);
}