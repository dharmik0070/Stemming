#include <stdio.h>
#include "addprefix.h"
#include "suffix.h"

void validate(char[]);


int main()
{
	char word[10];
	int i;
	int flag = 0;
	while (1)
	{
		printf("\n\n\n\t\t\t Enter a Word : ");
		gets(word);
		if (strlen(word) != 0 && strlen(word)<20)
		{
			
			for (i = 0; word[i] != '\0'; i++)
				//for (i = 0; (word[i] != '\0' || strlen(word) == 0); i++)
			{
				if (!isalpha(word[i]))
					//if (strlen(word) == 0 || !isalpha(word[i]))
				{
					flag = 1;
					printf("\n\t\t\tEntered Word is Not Valid !!!");
					break;
				}

			}
			printf("\n\t\t\t Your word is : %s ", word);
			if (flag == 0)
			{
				strlwr(word);
				validate(word);
			}
		}
		else
		{
			printf("\n\t\t\t Invalid Input.....");
		}
	}
	
	return 0;
}


void validate(char word[])
{
	int wordExist = 0;
	FILE *fp;
	char *prefix;
	int i;
	char words_in_root[15];
	char ch;
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\rootword.txt", "r");

	while (fgets(words_in_root, sizeof(words_in_root), fp))
	{
		words_in_root[strcspn(words_in_root, "\n")] = 0;
		int f = strcmp(word, words_in_root);
		//c = strcmp(word, words_in_root);
		if (f == 0)
		{
			wordExist = 1;
			//printf("\nexists word");
			addprefix(word); //call addprefix function
			//printf("%s", prefix[0]);
			break;
		}

	}

	fclose(fp);
	if (wordExist == 0)
		printf("\n\t\t\tWord Not Exists in root file"); 
	//call trimming function here.....

}