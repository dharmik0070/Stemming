#include "suffix.h"
#include <stdio.h>
#include <Windows.h>

void loadingBar();

char* str;

struct list
{
	char* string;
	struct list* next;
};

typedef struct list LIST;

/*
function name: addprefix
Purpose: 1. read prefix.txt file linewise and store it in linked list
		 2. adding string with the prefix in each node 
		 3. compare node->data with completeword(vocabulary.txt) file
		 4. if(true)then print node->data
		 5. call addsuffix function
input: user entered string
output: string with prefix 
*/

void addprefix(char word[])
{
	FILE* fp;
	int x;
	int prefixExist = 0;
	char line[50];
	LIST* current, * head, * node;
	int i;
	char* array[10];
	char completeword[50], prefix[50];
	head = current = NULL;
	fp = fopen("C:\\Users\\DELL\\Desktop\\sprint1\\prefix.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		LIST* node = malloc(sizeof(LIST));
		node->string = _strdup(line);
		node->string[strcspn(node->string, "\n")] = 0;
		strcpy(prefix, node->string);
		strcat(prefix, word);
		node->string = _strdup(prefix);
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


	fp = fopen("C:\\Users\\DELL\\Desktop\\sprint1\\vocabulary.txt", "r");

	printf("\n\n\t\t\t\t Words after adding Prefixes and Suffixes alone is/are : \n");
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
	addsuffix(word);
	for (current = head; current; current = current->next)
	{
		addsuffix(current->string);
	}
	fclose(fp);

}

/*
function name: trimprefix
Purpose: 1.open prefix.txt file
		 2.to check the length of prefix we call startswith()
		 3.strore the length of prefix in index variable
		 4.open rootword.txt file
		 5.compare string with rootword.txt file if it is present then we print the string
		 6.call trim suffix function
input:taken from user 
output: return string without prefix
*/


void trimprefix(char word[])
{
	FILE* fp, * fp1;
	char line[50];
	int index;
	char prefix[50], root[50];
	fp = fopen("C:\\Users\\DELL\\Desktop\\sprint1\\prefix.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		str = (char*)malloc(sizeof(char*));
		str = word;

		strcpy(prefix, line);
		prefix[strcspn(prefix, "\n")] = 0;
		index = startsWith(prefix, word);

		
		if (index != 0)
		{
			str += index; //str=str+index
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

//To check the length of the prefix

int startsWith(char* pre, char* str) 
{
	int lenprefix = strlen(pre), lenstring = strlen(str);

	if ((lenstring > lenprefix) && (memcmp(pre, str, lenprefix) == 0))
	{
		return lenprefix;
	}

	return 0;

}

/*
function name: loadingBar
*/

void loadingBar()
{

	char a = 177, b = 219;
	printf("\n");
	printf("\n\n\t\t\t\t\t\t   Adding Prefixes and Suffixes Both......  Please Wait .....\n\n");
	printf("\t\t\t\t\t\t\t\t  ");
	for (int i = 0; i < 26; i++)
		printf("%c", a);

	printf("\r");
	printf("\t\t\t\t\t\t\t\t  ");

	for (int i = 0; i < 26; i++) {
		printf("%c", b);

		
		Sleep(1000); // Sleep for 1 second 
	}
}