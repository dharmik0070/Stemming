#include <stdio.h>
#include "prefix.h"
#include "suffix.h"

void validate(char[]);


int main()
{
	char word[10];
	int i;
	int flag = 0;
	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    STEMMING    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	while (1)
	{
		printf("\n\n\n\t\t\t\t Enter a Word :  ");
		gets(word);
		if (strlen(word) != 0 && strlen(word) < 20)
		{

			for (i = 0; word[i] != '\0'; i++)
				
			{
				if (!isalpha(word[i]))
					
				{
					flag = 1;
					printf("\n\n\t\t\t\t Entered Word is Not Valid !!! ");
					break;
				}

			}
			printf("\n\n\t\t\t\t Your word is : %s ", word);
			printf("\n\n\t\t\t\t ______________________________________  PROCESSING......  ________________________________________\n");
			if (flag == 0)
			{
				strlwr(word);
				validate(word);
			}
		}
		else
		{
			printf("\n\n\t\t\t\t -----------------------------Invalid Input..... :(  Try Again.... --------------------------------\n");
		}


		printf("\n\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	}

	return 0;
}

/*
function name: validate
Purpose: 1. read rootword.txt file
		 2. check if user entered string is present in rootword or not
		 3. if present in rootword.txt file call addprefix function
		 4. else call trimprefix functiion
input: user entered string
*/
void validate(char word[])
{
	int wordExist = 0;
	FILE* fp;
	char* prefix;
	int i;
	char words_in_root[15];
	char ch;
	int f;
	fp = fopen("C:\\Users\\DELL\\Desktop\\sprint1\\rootword.txt", "r");

	while (fgets(words_in_root, sizeof(words_in_root), fp))
	{
		words_in_root[strcspn(words_in_root, "\n")] = 0;
		f = strcmp(word, words_in_root);
		if (f == 0)
		{
			wordExist = 1;
			addprefix(word); 
			break;
		}


	}


	fclose(fp);

	if (wordExist == 0)

		trimprefix(word);
	

}