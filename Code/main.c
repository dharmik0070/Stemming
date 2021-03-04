#include <stdio.h>
#include "prefix.h"
#include "suffix.h"
#include "PATH.h"

int main(void)
{
	char word[SIZE], prompt;
	int index, flag;
	

	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx   STEMMING  (By - CODE CAMPERS)   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	
	printf("\n\n\t\t\t\t ___________________________________________  HINT  _______________________________________________");
	printf("\n\n\t\t\t\t   1. If your word contains prefix or suffix, Stemmer will trim it. ");
	printf("\n\t\t\t\t   2. If it do not contain prefix / suffix, Stemmer will add it and display all possible words.  ");
	printf("\n\n\t\t\t\t __________________________________________________________________________________________________");
	while (1)
	{
		flag = 0;
		printf("\n\n\t\t\t\t\t\t\t  Press Enter Key to Continue Or Any Key To Exit  \n\t\t\t\t\t\t\t\t\t\t  ");
		prompt = getchar();
		if (prompt == 10)
		{
			printf("\n\n\n\t\t\t\t  Enter a Word :  ");
			gets(word);
			trimleadingandTrailing(word);
			if (strlen(word) > 0 && strlen(word) < 50)
			{

				printf("\n\n\t\t\t\t  Your word is : %s ", word);
				for (index = 0; word[index] != '\0'; index++)
				{
					if (!isalpha(word[index]))
					{
						flag = 1;
						printf("\n\n\t\t\t\t  Entered Word is Not Valid !!! ");
						break;
					}

				}
				
				if (flag == 0)
				{
					printf("\n\n\t\t\t\t ______________________________________   PROCESSING......  _______________________________________\n");
					strlwr(word); //convert string into lowecase.
					validate(word);
				}
			}
			else
			{
				printf("\n\n\t\t\t\t -----------------------------Invalid Input..... :(  Try Again.... --------------------------------\n");
			}


			printf("\n\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
			
		}
			else
			{
				printf("\n\n\t\t\t\t\t\t\t\tThank You For Using Our Application......\n\n ");
				printf("\n\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n\n\n");
				return;
			}

		
	}

	return 0;
}

/**************************************************************************
Function name: validate
Purpose: 1. Read rootword.txt file.
		 2. Check if user entered string is present in rootword or not.
		 3. If present in rootword.txt file call addprefix function.
		 4. Else call trimprefix functiion.
Input:  User entered string.
***************************************************************************/

void validate(char word[])
{
	int wordExist = 0,flag;
	FILE *fp=NULL;
	char words_in_root[SIZE];

	fp = fopen(ROOT, "r");
	//This if block is true when user enter the root word only.
	if (fp != NULL)
	{
		//Picking the words from root file line wise
		while (fgets(words_in_root, sizeof(words_in_root), fp))
		{
			//remove new line character from the words_in_root variable.
			words_in_root[strcspn(words_in_root, "\n")] = 0;
			flag = strcmp(word, words_in_root);
			if (flag == 0)
			{
				wordExist = 1;
				printf("\n\n\t\t\t\t\t  Prefixes or Suffixes will be Added.  Hold On!!  You Will get the Complete word(s)...\n");
				addprefix(word);
				break;
			}
		}

	}
	else
	{
		printf("\n\t\t\t\t  Root File do not exist."); 
		return;
	}
	

	fclose(fp);
	//If word donot exist in the root word file then wordExist=0.
	if (wordExist == 0)
	{
		
		printf("\n\n\t\t\t\t\t\t  Trimming will be done.  Hold On!!  You Will get the Root word...\n\n");
		trimprefix(word);

	}
	
}

/**********************************************************************
Function name: trimleadingandTrailing
Purpose: 1. Read the String.
		 2. Remove starting and ending space and tabs from the string.
Input:  User entered string.
***********************************************************************/


void trimleadingandTrailing(char *word)
{
	int  index1, index2;

	for (index1 = 0; word[index1] == ' ' || word[index1] == '\t'; index1++); //remove starting space
	
	for (index2 = 0; word[index1]; index1++)
	{
		word[index2++] = word[index1];
	}
	word[index2] = '\0';

	for (index1 = 0; word[index1] != '\0'; index1++) //remove ending spaces
	{
		if (word[index1] != ' ' && word[index1] != '\t')
			index2 = index1;
	}
	

	word[index2 + 1] = '\0';
}


//string = "  happy  "   
//string = "happy  \0"
//string = "happy"