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
	char line[50];
	LIST *current, *head, *node;
	int i, suffixExist = 0;
	char *array[10];
	char completeword[50], suffix[50];
	head = current = NULL;
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\suffic.txt", "r");
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
	/*for (current = head; current; current = current->next)
	{
		printf("%s\n", current->string);
	}
	*/
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\vocabulary.txt", "r");
	
	//printf("\n\t\t\t Words after adding suffixes are : \n");
	while (fgets(completeword, sizeof(completeword), fp))
	{
		
		completeword[strcspn(completeword, "\n")] = 0; //remove \n from the line
		for (current = head, i = 0; current; current = current->next)
		{
			
			if (strcmp(completeword, current->string) == 0)
			{
				//suffixExist = 1;
				array[i] = malloc(strlen(current->string) + 1);
				if (array[i])
				{
					strcpy(array[i], current->string);
					printf("\n\t\t\t\t%s", array[i]);
				}
				i++;

			}

		}

	}
	fclose(fp);
	//if (suffixExist == 0)
		//printf("\n\t\t\t Complete Valid Words to the Given Word are not available...... ");
	
	
}









