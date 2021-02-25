#include "suffix.h"
#include <stdio.h>


struct list
{
	char *string;
	struct list *next;
};

typedef struct list LIST;

void addprefix(char word[])
{
	FILE *fp;
	int prefixExist = 0;
	char line[50];
	LIST *current, *head, *node;
	int i;
	char *array[10];
	char completeword[50], prefix[50];
	head = current = NULL;
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\prefix.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		LIST *node = malloc(sizeof(LIST));
		node->string = strdup(line);
		node->string[strcspn(node->string, "\n")] = 0;
		strcpy(prefix, node->string);
		strcat(prefix, word);
		node->string = strdup(prefix);
		strcpy(node->string, prefix);

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
	
	printf("\n\n\t\t\t Words after adding Prefixes and Suffixes are : \n");
	while (fgets(completeword, sizeof(completeword), fp))
	{
		
		completeword[strcspn(completeword, "\n")] = 0; //remove \n from the line
		for (current = head, i = 0; current; current = current->next)
		{
			
			if (strcmp(completeword, current->string) == 0)
			{
				//prefixExist = 1;
				
				array[i] = malloc(strlen(current->string) + 1);
				if (array[i])
				{
					strcpy(array[i], current->string);
					printf("\n\t\t\t\t%s", array[i]);
				}
				
				//addsuffix(current->string);
				i++;

			}		

		}

	}
	addsuffix(word);
	for (current = head; current; current = current->next)
	{
		//printf("%s\n", current->string);
		addsuffix(current->string);
	}
	fclose(fp);
	

}
