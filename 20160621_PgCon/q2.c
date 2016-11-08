#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MAX_CARDTYPE ( 13 )
#define NUM_MAX_DATA   ( 13 * 4 )
#define MAX_INPUT_LEN  ( 100000 )
#define NO_DATA        ( 9999 )

int split(char *str, const char *delim, char *outlist[]);
int init_list(char** list, int n);
int count_list(char** list, int n);
int init_card_list(int* list, int n);
int print_data_list(char** list);
int print_num_list(int *list);
int compare_int(const void* a, const void* b);

int ListSpade[NUM_MAX_CARDTYPE + 1];
int ListDiamond[NUM_MAX_CARDTYPE + 1];
int ListClub[NUM_MAX_CARDTYPE + 1];
int ListHeart[NUM_MAX_CARDTYPE + 1];


int main() {

	char  InputLine[MAX_INPUT_LEN] = "";
	char* DataList[NUM_MAX_DATA + 1];
	int   iSpade = 0, iDiamond = 0, iClub = 0, iHeart = 0;

	int ret = 0;
	int count = 0;
	char* ret_fgets = NULL;
	char data_str[2] = "";
	int data_num = 0;
	int i = 0;

	/* Init input list*/
	init_list(DataList, NUM_MAX_DATA + 1);
	init_card_list(ListSpade, NUM_MAX_CARDTYPE + 1);
	init_card_list(ListDiamond, NUM_MAX_CARDTYPE + 1);
	init_card_list(ListClub, NUM_MAX_CARDTYPE + 1);
	init_card_list(ListHeart, NUM_MAX_CARDTYPE + 1);
	
	/* Get all data */
	ret_fgets = fgets(InputLine, sizeof(InputLine), stdin);
	if (ret_fgets != NULL)
	{
		count = split(InputLine, " \n", DataList);
	}

	for (i = 0; i < count && (DataList[i] != NULL); i++)
	{
		if (DataList[i][1] == 'A')
			data_num = 1;
		else if (DataList[i][1] == '0')
			data_num = 10;
		else if (DataList[i][1] == 'J')
			data_num = 11;
		else if (DataList[i][1] == 'Q')
			data_num = 12;
		else if (DataList[i][1] == 'K')
			data_num = 13;
		else
		{
			data_str[0] = DataList[i][1];
			data_num = atoi((const char*)data_str);
		}

		if (DataList[i][0] == 'S')
			ListSpade[iSpade++] = data_num;
		else if (DataList[i][0] == 'D')
			ListDiamond[iDiamond++] = data_num;
		else if (DataList[i][0] == 'C')
			ListClub[iClub++] = data_num;
		else if (DataList[i][0] == 'H')
			ListHeart[iHeart++] = data_num;
		else
			printf("***** Error data card *****\n");
	}
	
	qsort(ListSpade, NUM_MAX_CARDTYPE, sizeof(int), compare_int);
	qsort(ListDiamond, NUM_MAX_CARDTYPE, sizeof(int), compare_int);
	qsort(ListClub, NUM_MAX_CARDTYPE, sizeof(int), compare_int);
	qsort(ListHeart, NUM_MAX_CARDTYPE, sizeof(int), compare_int);

	/* Print data */
	if (ListSpade[0] != NO_DATA)
	{
		printf("S:");
		print_num_list(ListSpade);
	}
	if (ListDiamond[0] != NO_DATA)
	{
		printf("D:");
		print_num_list(ListDiamond);
	}
	if (ListClub[0] != NO_DATA)
	{
		printf("C:");
		print_num_list(ListClub);
	}
	if (ListHeart[0] != NO_DATA)
	{
		printf("H:");
		print_num_list(ListHeart);
	}

	return 0;
}

int split(char *str, const char *delim, char *outlist[])
{
	char *token;
	int count = 0;
	char *next_token = NULL;
	
	//token = strtok_s(str, delim, &next_token);
	token = strtok(str, delim);
	while ((token != NULL) && (count < NUM_MAX_DATA)) {
		outlist[count++] = token;
		//token = strtok_s(NULL, delim, &next_token);
		token = strtok(NULL, delim);
	}
	return count;
}

int init_list(char** list, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		list[i] = NULL;
	}

	return i;
}

int init_card_list(int* list, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		list[i] = NO_DATA;
	}

	return i;
}

int count_list(char** list, int n)
{
	int i = 0;
	int count = 0;

	for (i = 0; i < n && (list[i] != NULL) ; i++)
	{
		count++;
	}

	return count;
}

int print_data_list(char** list)
{
	int i = 0;

	while (list[i] != NULL)
	{
		printf("[%d] [%s]\n", i, list[i]);
		i++;
	}

	return i;
}

int print_num_list(int *list)
{
	int i = 0;
	char print_char[2] = "";

	while (list[i] != NO_DATA)
	{
		if (list[i] == 1)
			sprintf(print_char, "%c", 'A');
		else if (list[i] == 10)
			sprintf(print_char, "%c", '0');
			//print_char[0] = '0';
		else if (list[i] == 11)
			sprintf(print_char, "%c", 'J');
			//print_char[0] = 'J';
		else if (list[i] == 12)
			sprintf(print_char, "%c", 'Q');
			//print_char[0] = 'Q';
		else if (list[i] == 13)
			sprintf(print_char, "%c", 'K');
			//print_char[0] = 'K';
		else
			sprintf(print_char, "%d", list[i]);

		printf("%s", print_char);
		if (list[i + 1] != NO_DATA)
		{
			printf(",");
		}

		i++;
	}

	printf("\n");

	return i;
}


int compare_int(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}
