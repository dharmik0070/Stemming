#include <stdio.h>

struct list
{
	char *string;
	struct list *next;
};

typedef struct list LIST;

int main(void)
{
	FILE *fp;
	char line[50];
	int i;
	LIST *current, *head;
	char word[100],suffix[50],completeword[50];
	printf("\nEnter word:\n");
	//word = (char*)malloc(sizeof(char));
	gets(word);
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
		//node = realloc(node, (strlen(node)));
	
	}
	fclose(fp);
	/*for (current = head; current; current = current->next)
	{
		printf("%s\n", current->string);
	}
	*/
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\vocabulary.txt", "r");

	while (fgets(completeword, sizeof(completeword), fp))
	{
		completeword[strcspn(completeword, "\n")] = 0; 
		for (current = head; current; current = current->next)
		{

			if (strcmp(completeword, current->string) == 0)
			{
				printf("%s\n", current->string);
			}
		}
		//printf("%s", completeword);

	}
	fclose(fp);
	
	return 0;
}