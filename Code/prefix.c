#include "prefix.h"
#include <stdio.h>
#include "PATH.h"

char *str = NULL;

struct list
{
	char *string;
	struct list *next;
};

typedef struct list LIST;

/**********************************************************************
Function name: addprefix
Purpose: 1. Read prefix.txt file linewise and store it in linked list.
		 2. Adding string with the prefix in each node.
		 3. Compare node->data with completeword(vocabulary.txt) file.
		 4. If(true)then print node->data.
		 5. Call addsuffix function.
Input:	User entered string.
Output: String with prefix.
***********************************************************************/

void addprefix(char word[])
{
	FILE *fp = NULL;
	LIST *current, *head, *node;
	head = current = NULL;
	
	int NA = 0, NAP = 0, *na = &NA;
	//NA = Flag for Not Applicable.
	//NAP = Flag for Not Applicable prefix.

	char line[SIZE], completeword[SIZE], prefix[SIZE];

	fp = fopen(PREFIX, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			LIST* node = (LIST*)malloc(sizeof(LIST));
			node->string = strdup(line);  //strdup is a function which will copy the line into the string part of the node.
			node->string[strcspn(node->string, "\n")] = 0;  //Removing the '\n' from the string part of the node.
			strcpy(prefix, node->string);
			strcat(prefix, word);   //Concatening the prefix with the word variable.
			node->string = strdup(prefix);
			

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

	NA=addsuffix(word,*na);  //Calling addsuffix function and return NA.
	if (NA == 0 && NAP == 0)
	{
		printf("\n\t\t\t\t  N/A");
	}

	printf("\n\n\t\t\t\t  Words after Adding Prefixes and Suffixes Both is/are :  \n");
	NA = 0;
	for (current = head; current; current = current->next)
	{
		//Here input is word with prefix
		NA=addsuffix(current->string,*na);	
		
	}
	if (NA != 1)
	{
		printf("\n\t\t\t\t  N/A");
	}
	
	fclose(fp);
	
	
}


/******************************************************************************************
Function name: trimprefix
Purpose: 1.Open prefix.txt file.
		 2.To check the length of prefix we call startswith().
		 3.Strore the length of prefix in index variable.
		 4.Open rootword.txt file.
		 5.Compare string with rootword.txt file if it is present then we print the string.
		 6.Call trim suffix function.
Input:	Taken from user.
Output: Return string without prefix.
*******************************************************************************************/

void trimprefix(char word[])
{
	FILE *fp = NULL, *fp1 = NULL;
	char line[SIZE], prefix[SIZE], root[SIZE];
	int index;
	fp = fopen(PREFIX, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			//Allocating memory to the str variable which point the word entered by the user.
			str = (char*)malloc(sizeof(char*));
			str = word;
			strcpy(prefix, line);
			prefix[strcspn(prefix, "\n")] = 0;
			//Calling startsWith function which contain prefix, word as a parameter
			// and return the length of the prefix .
			index = startsWith(prefix, word);
			if (index != 0)
			{
				//Reassigning str variable after trimming matched prefix.
				//E.g. str = unhappy, prefix = un,index = 2
				//now str+= 2 i.e., str= happy.

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

//To check the length of the prefix.

int startsWith(char *prefix, char *str)
{
	int lenprefix = strlen(prefix), lenstring = strlen(str);

	if ((lenstring > lenprefix) && (memcmp(prefix, str, lenprefix) == 0))
	{
		return lenprefix;
	}

	return 0;

}

