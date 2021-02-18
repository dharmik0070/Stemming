#include<stdio.h>
#include<string.h>
void validate(char);
int main()
{
	int i;
	char word[10];
	printf("enter a word");
	gets(word);
	for (i = 0; word[i] != '\0'; i++)
	{
		if (!isalpha(word[i]))
		{
			printf("entered word is not valid");
			exit();
		}
	}
	validate(word);
	return 0;


}
void validate(char word[])
{
	int wordExist = 0;
	FILE* fp;
	char words_in_root[15];
	char ch;
	fp = fopen("C:\\Users\\DELL\\Desktop\\rootword.txt", "r"); 
	
	while (fgets(words_in_root, sizeof(words_in_root), fp))
	{
		words_in_root[strcspn(words_in_root, "\n")] = 0;
		int fp = strcmp(word, words_in_root);
		//c = strcmp(word, words_in_root);
		if (fp == 0)
		{
			wordExist = 1; 
			printf("word exist in rootword file");//call addprefix function
			exit(0);


		}
	}
		//fclose(fp);
		if (wordExist == 0)
			//printf("word exist");
		//else
			printf("word not exist in root word file");


		
	
	
}