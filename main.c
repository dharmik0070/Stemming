#include <stdio.h>
#include "prefix.h"
#include "suffix.h"
#include "PATH.h"

void validate(char[]);

int main(void)
{
	char word[10], prompt;
	int index, flag;


	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    STEMMING    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	printf("\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	
	
	while (1)
	{
		flag = 0;
		printf("\n\n\t\t\t\t\t\t\t\t    Press Enter Key to Continue  \n\t\t\t\t\t\t\t\t\t\t  ");
		prompt = getchar();
		if (prompt == 10)
		{
			printf("\n\n\n\t\t\t\t  Enter a Word :  ");
			gets(word);
			if (strlen(word) > 0 && strlen(word) < 20)
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
			else
			{
				printf("\n\n\t\t\t\t\t\t\t\tThank You For Using Our Application......\n\n ");
				printf("\n\n\t\t\t\t xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n\n\n");
				return;
			}

		
	}

	return 0;
}


void validate(char word[])
{
	int wordExist = 0,flag;
	FILE *fp=NULL;
	char words_in_root[15],ch;

	fp = fopen(ROOT, "r");
	if (fp != NULL)
	{
		while (fgets(words_in_root, sizeof(words_in_root), fp))
		{
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
	
	if (wordExist == 0)
	{
		
		printf("\n\n\t\t\t\t\t\t  Trimming will be done.  Hold On!!  You Will get the Root word...\n\n");
		trimprefix(word);

	}
	
}