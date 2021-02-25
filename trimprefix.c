#include <stdio.h>


int startsWith(char *pre, char *str);

char *str;

int main()
{
	char word[50];
	printf("\n\n\n\t\t\t Enter a Word : ");
	gets(word);
	trimprefix(word);

	return 0;
}

void trimprefix(char word[])
{
	FILE *fp,*fp1;
	char line[50];
	int index;
	char prefix[50],root[50];
	fp = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\prefix.txt", "r");
	while (fgets(line, sizeof(line), fp))
	{
		str = (char*)malloc(sizeof(char*));
		str = word;
		
		strcpy(prefix, line);
		prefix[strcspn(prefix, "\n")] = 0;
		//printf("\n%s", prefix);
		index=startsWith(prefix, word);

		//printf("\n%d", index);
		if (index != 0)
		{
			//memmove(word, prefix, strlen(word) - index);
			str += index;
			fp1 = fopen("C:\\Users\\tina\\Desktop\\Capgemini training material\\Project\\rootword.txt", "r");
			while (fgets(root, sizeof(root), fp1))
			{
				
				root[strcspn(root, "\n")] = 0;
				
				if (strcmp(root, str) == 0)
				{
					printf("\n\t\t\t Word After Removing Prefix is :  %s", str);
				}
			}
			
			fclose(fp1);
			//printf("%s", prefix);
			//printf("%s", word);
		}
		

	}
	
	fclose(fp);

}

int startsWith(char *pre,char *str)
{
	int lenprefix = strlen(pre),lenstring = strlen(str);

	if ((lenstring > lenprefix) && (memcmp(pre, str, lenprefix) == 0))
	{
			return lenprefix;
	}
	
	return 0;
	
}