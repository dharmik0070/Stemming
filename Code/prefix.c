#include "suffix.h"
#include <stdio.h>

char *str = NULL;

struct list
{
	char *string;
	struct list *next;
};

typedef struct list LIST;

void addprefix(char word[])
{
	FILE *fp = NULL;
	int prefixExist = 0, index;
	char line[50], completeword[50], prefix[50], *array[10];
	LIST *current, *head, *node;
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
	
	printf("\n\n\t\t\t\t  Words after adding Prefixes and Suffixes alone is/are :  ");
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
					
					printf("\n\t\t\t\t  ->  %s",array[index]);
				}
				
				index++;

			}		

		}

	}
	addsuffix(word);
	printf("\n\n\t\t\t\t  Words after Adding Prefixes and Suffixes Both is/are :  \n");

	for (current = head; current; current = current->next)
	{
		addsuffix(current->string);
	}
	fclose(fp);
	

}


void trimprefix(char word[])
{
	FILE *fp = NULL, *fp1 = NULL;
	char line[50], prefix[50], root[50];
	int index;
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\prefix.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		str = (char*)malloc(sizeof(char*));
		str = word;

		strcpy(prefix, line);
		prefix[strcspn(prefix, "\n")] = 0;
		index = startsWith(prefix, word);
		if (index != 0)
		{
			str += index;
			fp1 = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\rootword.txt", "r");
			while (fgets(root, sizeof(root), fp1))
			{
				
				root[strcspn(root, "\n")] = 0;

				if (strcmp(root, str) == 0)
				{
					printf("\n\t\t\t\t  Word After Removing Prefix is :  %s", str);
				}
			}

			fclose(fp1);
		}


	}
	
	trim_suffix(word);
	
	fclose(fp);

}

int startsWith(char *prefix, char *str)
{
	int lenprefix = strlen(prefix), lenstring = strlen(str);

	if ((lenstring > lenprefix) && (memcmp(prefix, str, lenprefix) == 0))
	{
		return lenprefix;
	}

	return 0;

}

