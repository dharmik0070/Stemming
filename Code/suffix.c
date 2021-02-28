#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct list
{
	char *string;
	struct list *next;
};

typedef struct list LIST;

void *addsuffix(char word[])
{
	FILE *fp;
	int index, suffixExist = 0;
	char line[50], completeword[50], suffix[50], *array[10];
	LIST *current, *head, *node;
	head = current = NULL;
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\suffix.txt", "r");
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
	fclose(fp);
	
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\vocabulary.txt", "r");
	
	while (fgets(completeword, sizeof(completeword), fp))
	{
		completeword[strcspn(completeword, "\n")] = 0;
		for (current = head, index = 0; current; current = current->next)
		{
			
			if (strcmp(completeword, current->string) == 0)
			{
				array[index] = malloc(strlen(current->string) + 1);
				if (array[index])
				{
					strcpy(array[index], current->string);
					printf("\n\t\t\t\t  ->  %s", array[index]);
				}
				index++;

			}

		}

	}
	fclose(fp);

}
