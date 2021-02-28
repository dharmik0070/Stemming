#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct list
{
	char* string;
	struct list* next;
};

typedef struct list LIST;

/*
function name: addsuffix
Purpose: 1. read suffic.txt file linewise and store it in linked list
		 2. adding string with the suffix in each node
		 3. compare node->data with completeword(vocabulary.txt) file
		 4. if(true)then print node->data
input: user entered string
output: string with suffix
*/

void* addsuffix(char word[])
{
	FILE* fp;
	char line[50];
	LIST* current, * head, * node;
	int i, suffixExist = 0;
	char* array[10];
	char completeword[50], suffix[50];
	head = current = NULL;
	fp = fopen("C:\\Users\\DELL\\Desktop\\sprint1\\suffic.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		LIST* node = malloc(sizeof(LIST));
		strcpy(suffix, word);
		node->string = _strdup(line);
		node->string[strcspn(node->string, "\n")] = 0;
		strcat(suffix, node->string);
		node->string = _strdup(suffix);
		strcpy(node->string, suffix);

		node->next = NULL;

		if (head == NULL)
		{
			current = head = node;
		}
		else
		{
			current = current->next = node;
		}

	}
	fclose(fp);
	fp = fopen("C:\\Users\\DELL\\Desktop\\sprint1\\vocabulary.txt", "r");

	while (fgets(completeword, sizeof(completeword), fp))
	{

		completeword[strcspn(completeword, "\n")] = 0; //remove \n from the line
		for (current = head, i = 0; current; current = current->next)
		{

			if (strcmp(completeword, current->string) == 0)
			{

				array[i] = malloc(strlen(current->string) + 1);
				if (array[i])
				{
					strcpy(array[i], current->string);
					printf("\n\t\t\t\t  ->  %s", array[i]);
				}
				i++;

			}

		}

	}
	fclose(fp);
}









