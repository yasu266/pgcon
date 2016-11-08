#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN  ( 1000 )

int main() {

	char InputLine[MAX_INPUT_LEN + 1 + 1] = "";
	int  i = 0;
	int  len = 0;

	fgets(InputLine, sizeof(InputLine), stdin);

	len = strlen(InputLine);
	
	for (i = len - 1 - 1; i >= 0; i--)
	{
		printf("%c", InputLine[i]);
	}

	printf("\n");

	return 0;
}
