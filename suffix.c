#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "PATH.h"

struct list
{
	char *string;
	struct list *next;
};

typedef struct list LIST;

int addsuffix(char word[], int *NA)
{
	FILE *fp;
	int index;
	char line[50], completeword[50], suffix[50], *array[10];
	LIST *current, *head, *node;
	head = current = NULL;
	fp = fopen(SUFFIX, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			LIST *node = malloc(sizeof(LIST));
			strcpy(suffix, word);
			node->string = strdup(line);
			node->string[strcspn(node->string, "\n")] = 0;
			strcat(suffix, node->string);
			node->string = strdup(suffix);
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
	}
	else
	{
		printf("\n\t\t\t\t  Suffix File do not exist.");
		return;
	}
	fclose(fp);
	
	fp = fopen(VOCABULARY, "r");
	
	if (fp != NULL)
	{
		while (fgets(completeword, sizeof(completeword), fp))
		{
			completeword[strcspn(completeword, "\n")] = 0;
			for (current = head; current; current = current->next)
			{

				if (strcmp(completeword, current->string) == 0)
				{
					NA = 1;
					
					printf("\n\t\t\t\t  ->  %s", current->string);

				}


			}

		}

	}
	else
	{
		printf("\n\t\t\t\t  Vocabulary File do not exist.");
		return;
	}

	fclose(fp);
	return NA;
}
