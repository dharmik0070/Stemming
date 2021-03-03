#include "suffix.h"
#include <stdio.h>
#include "PATH.h"

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
	LIST *current, *head, *node;
	head = current = NULL;
	int NA = 0, NAP = 0, *na = &NA;
	char line[50], completeword[50], prefix[50], *array[10], *suffix[10];

	fp = fopen(PREFIX, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			LIST *node = (LIST *)malloc(sizeof(LIST));
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
	}
	else
	{
		printf("\n\t\t\t\t  Prefix File do not exist.");
		return;
	}
	fclose(fp);
	
	
	fp = fopen(VOCABULARY, "r");
	
	printf("\n\n\t\t\t\t  Words after adding Prefixes and Suffixes alone is/are :  \n");
	if (fp != NULL)
	{
		while (fgets(completeword, sizeof(completeword), fp))
		{

			completeword[strcspn(completeword, "\n")] = 0;
			for (current = head; current; current = current->next)
			{

				if (strcmp(completeword, current->string) == 0)
				{
					NAP= 1;
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

	NA=addsuffix(word,*na);
	if (NA == 0 && NAP == 0)
	{
		printf("\n\t\t\t\t  N/A");
	}

	printf("\n\n\t\t\t\t  Words after Adding Prefixes and Suffixes Both is/are :  \n");
	NA = 0;
	for (current = head; current; current = current->next)
	{
		NA=addsuffix(current->string,*na);	
		
	}
	if (NA != 1)
	{
		printf("\n\t\t\t\t  N/A");
	}
	
	fclose(fp);
	
	
}


void trimprefix(char word[])
{
	FILE *fp = NULL, *fp1 = NULL;
	char line[50], prefix[50], root[50];
	int index;
	fp = fopen(PREFIX, "r");
	if (fp != NULL)
	{
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
				fp1 = fopen(ROOT, "r");
				if (fp1 != NULL)
				{
					while (fgets(root, sizeof(root), fp1))
					{

						root[strcspn(root, "\n")] = 0;

						if (strcmp(root, str) == 0)
						{
							printf("\n\t\t\t\t  Word After Removing Prefix is :  %s", str);
						}
					}
				}
				else
				{
					printf("\n\t\t\t\t  Root File do not exist.");
					return;
				}

				fclose(fp1);
			}


		}
	}
	else
	{
		printf("\n\t\t\t\t  Prefix File do not exist.");
		return;
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

