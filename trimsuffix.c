#include <stdio.h>
#include "prefix.h"
#include "suffix.h"
#include "PATH.h"


#define TRUE 1
#define FALSE 0
int index;
char* word = NULL;
char* str;

void  trim_suffix(char* word)
{
	char root[50];
	str = (char*)malloc(sizeof(char*) * strlen(word));
	str = return_str(word);
	if (strcmp(str, word) == 0)
		printf("\n\n\t\t\t\t  Suffix can not be removed in the given word....", word);
	else

	printf("\n\t\t\t\t  Word After Removing Suffix is :  %s", str);

}

char* return_str(char* word)
{
	char* temp;
	temp = (char*)malloc(sizeof(char*));
	strcpy(temp, word);
	if (step1_a_b(temp) != NULL)
		return temp;
	else if (step_1_c(temp) != NULL)
		return temp;
	else if (step_2(temp) != NULL)
		return temp;
	else if (step_3(temp) != NULL)
		return temp;
	else if (step_4(temp) != NULL)
		return temp;
	else
		step_5(temp);
	
	return temp;
}
int cons(int index, char* str)
{
	if (str[index] == 'a' || str[index] == 'e' || str[index] == 'i' || str[index] == 'o' || str[index] == 'u')
	{
		return FALSE;
	}
	else
		return TRUE;
}
int degree_m(char* str)
{
	int count = 0;
	int length;
	length = strlen(str);
	for (index = 0; index < length - 1; index++)
	{
		if (!cons(index, str))
		{
			if (cons(index + 1, str) && length > 0)
			{
				count++;
			}
		}
	}
	return count;
}
int vowel_stem(char* str)
{
	int flag = 0;
	for (index = 0; str[index]; index++)
	{
		if (!cons(index, str))
		{
			flag = 1;
		}
	}
	return flag;
}
int double_cons(char* str) {
	int length;
	length = strlen(str);
	if (cons(length - 1, str) && str[length - 1] == str[length - 2])
	{
		return 1;
	}
	return 0;
}
int cons_vowel_cons(char* str) {
	int length;
	char ch;
	length = strlen(str);
	ch = str[length - 1];
	if (cons(length - 1, str) && !cons(length - 2, str) && cons(length - 3, str))
	{
		if (ch == 'w' || ch == 'x' || ch == 'y')
			return 0;
		return 1;
	}
	return 0;
}
int end_s(char* str, char ch)
{
	int length;
	length = strlen(str);
	if (str[length - 1] == ch)
	{
		return 1;
	}
	return 0;
}

char* cleanup_1(char* string1ab)
{
	int length;
	length = strlen(string1ab);
	if (string1ab[length - 1] == 't' && string1ab[length - 2] == 'a')
	{
		string1ab[length] = 'e';
		string1ab[length + 1] = '\0';

	}
	else if (string1ab[length - 1] == 'l' && string1ab[length - 2] == 'b')
	{
		string1ab[length] = 'e';
		string1ab[length + 1] = '\0';

	}

	else if (!(end_s(string1ab, 'l') || end_s(string1ab, 's') || end_s(string1ab, 'z')) && double_cons(string1ab))
	{
		string1ab[length - 1] = '\0';

	}
	else if (degree_m(string1ab) == 1 && cons_vowel_cons(string1ab))
	{

		string1ab[length] = 'e';
		string1ab[length + 1] = '\0';
	}

	return string1ab;
}
char* step1_a_b(char* temp)
{
	word = NULL;
	int length;
	length = strlen(temp);
	if (end_s(temp, 's'))
	{
		if (temp[length - 2] == 'e' && temp[length - 3] == 'i')
		{
			temp[length - 2] = '\0';
			word = temp;
		}
		else if (temp[length - 2] == 'e' && temp[length - 3] == 's' && temp[length - 4] == 's')
		{
			temp[length - 2] = '\0';
			word = temp;
		}
		else if (temp[length - 2] == 's' && temp[length-3]!='e' && temp[length - 3] != 'n')
		{
			temp[length - 1] = '\0';
			word = temp;
		}
		

	}
	else if (temp[length - 1] == 'd' && temp[length - 2] == 'e' && temp[length - 3] == 'e')
	{
		char eed[30];
		strcpy(eed, temp);
		if (strlen(eed) > 3) {
			strcpy(eed, substring_return(eed, 3));
			if (degree_m(eed) > 0) {
				temp[length - 1] = '\0';
			}
			word = temp;
		}
	}
	else if (temp[length - 1] == 'd' && temp[length - 2] == 'e')
	{

		char ed[30];
		strcpy(ed, temp);
		if (strlen(ed) > 2) {

			strcpy(ed, substring_return(ed, 2));

			if (vowel_stem(ed)) 
			{
				word=cleanup_1(ed);
				strcpy(temp, word);
			}
		}
	}
	else if (temp[length - 1] == 'g' && temp[length - 2] == 'n' && temp[length - 3] == 'i')
	{
		char ing[30];
		strcpy(ing, temp);
		if (strlen(ing) > 3)
		{
			strcpy(ing, substring_return(ing, 3));

			if (vowel_stem(ing))
			{
				word = cleanup_1(ing);
				strcpy(temp, word);
			}		
		}

	}
	else if (temp[length - 1] == 'r' && temp[length - 2] == 'e' && temp[length-3]!='z')
	{
		char er[30];
		strcpy(er, temp);
		if (strlen(er) > 2)
		{
			strcpy(er, substring_return(er, 2));

			if (vowel_stem(er))
			{
				word = cleanup_1(er);
				strcpy(temp, word);
			}
		}

	}
	return word;
}
char* step_1_c(char* temp)
{
	word = NULL;
	int length;
	length = strlen(temp);
	if (vowel_stem(temp) && temp[length - 1] == 'y')
	{
		temp[length - 1] = 'i';
		temp[length] = '\0';
		word = temp;
	}
	
	return word;
}
char* step_2(char* temp) {
	word = NULL;
	int length;
	length = strlen(temp);
	char step2[30];
	strcpy(step2, temp);
	if (strlen(step2) > 7) {
		strcpy(step2, substring_return(step2, 7));
		if ((length > 7 && degree_m(step2) > 0) &&
			(temp[length - 1] == 'l' && temp[length - 2] == 'a' &&
				temp[length - 3] == 'n' && temp[length - 4] == 'o' &&
				temp[length - 5] == 'i' && temp[length - 6] == 't' && temp[length - 7] == 'a'))
		{
			temp[length - 5] = 'e';
			temp[length - 4] = '\0';
			word = temp;
		}
		if (temp[length - 1] == 'l' && temp[length - 2] == 'a' &&
			temp[length - 3] == 'n' && temp[length - 4] == 'o' &&
			temp[length - 5] == 'i' && temp[length - 6] == 't')
		{
			strcpy(step2, temp);
			strcpy(step2, substring_return(step2, 2));
			if (degree_m(step2) > 0) {
				temp[length - 2] = '\0';
				word = temp;
			}
		}
		else if ((length > 7 && degree_m(step2) > 0) &&
			(temp[length - 1] == 'n' && temp[length - 2] == 'o' &&
				temp[length - 3] == 'i' && temp[length - 4] == 't' &&
				temp[length - 5] == 'a' && temp[length - 6] == 'z' && temp[length - 7] == 'i'))
		{
			temp[length - 5] = 'e';
			temp[length - 4] = '\0';
			word = temp;
		}

		else if ((length > 6) && temp[length - 1] == 'i' &&
			temp[length - 2] == 't' && temp[length - 3] == 'i' &&
			temp[length - 4] == 'l' && temp[length - 5] == 'i' && temp[length - 6] == 'b')
		{
			strcpy(step2, temp);
			strcpy(step2, substring_return(step2, 6));
			if (degree_m(step2) > 0) {
				temp[length - 5] = 'l';
				temp[length - 4] = 'e';
				temp[length - 3] = '\0';
				word = temp;
			}
			
		}
	}
	return word;
	
}
char* step_3(char* temp) {
	word = NULL;
	int length = strlen(temp);
	char step3[30];
	strcpy(step3, temp);
	if (temp[length - 1] == 'l' && temp[length - 2] == 'u' && temp[length - 3] == 'f')
	{
		strcpy(step3, substring_return(step3, 3));
		if (degree_m(step3) > 0)	
		{
			temp[length - 3] = '\0';
			word = temp;
		}

	}
	if (temp[length - 1] == 's' && temp[length - 2] == 's' && temp[length - 3] == 'e' && temp[length - 4] == 'n')
	{
		strcpy(step3, substring_return(step3, 4));
		if (degree_m(step3) > 0)	
		{
			temp[length - 4] = '\0';
			word = temp;
			
		}

	}
	if (temp[length - 1] == 'e' && temp[length - 2] == 't' &&
		temp[length - 3] == 'a' && temp[length - 4] == 'c' && temp[length - 5] == 'i')
	{
		strcpy(step3, substring_return(step3, 5));
		if (degree_m(step3) > 0) 
		{
			temp[length - 3] = '\0';
			word = temp;
		}
	}
	
	return word;
}
char* step_4(char* temp) {
	word = NULL;

	int length = strlen(temp);
	char step4[30];
	strcpy(step4, temp);
	if (strlen(step4) > 4) {

		strcpy(step4, substring_return(step4, 4));
		if ((length > 4 && degree_m(step4) > 0) &&
			(temp[length - 1] == 'e' && temp[length - 2] == 'c' &&
				temp[length - 3] == 'n' && temp[length - 4] == 'a'))
		{
			temp[length - 4] = '\0';
			word = temp;
		}
		else if (length > 3 && temp[length - 1] == 't' && temp[length - 2] == 'n' && temp[length - 3] == 'e')
		{
			strcpy(step4, temp);
			strcpy(step4, substring_return(step4, 3));
			if (degree_m(step4) > 0) {
				temp[length - 3] = '\0';
				word = temp;
			}
		}
		else if (length > 3 && temp[length - 1] == 'e' && temp[length - 2] == 'v' && temp[length - 3] == 'i')
		{
			strcpy(step4, temp);
			strcpy(step4, substring_return(step4, 3));
			if (degree_m(step4) > 0) {
				temp[length - 3] = '\0';
				word = temp;
			}
		}
	}
	
	return word;
}
char* step_5(char* temp)
{
	word = NULL;
	int length = strlen(temp);
	char step5[30];
	strcpy(step5, temp);
	if (strlen(step5) > 4) {
		strcpy(step5, substring_return(step5, 1));
		if (length > 1 && degree_m(step5) > 1 && (temp[length - 1] == 'e'))
		{
			temp[length - 1] = '\0';
			word = temp;
		}
		else if (length > 4 && end_s(temp, 's') && (temp[length - 2] == 's') &&
			(temp[length - 3] == 'e') && (temp[length - 4] == 'n'))
		{
			strcpy(step5, temp);
			strcpy(step5, substring_return(step5, 4));
			if (degree_m(step5) == 1 && !cons_vowel_cons(step5)) {
				temp[length - 4] = '\0';
				word = temp;
			}
		}

		else if (length > 2 && double_cons(temp) && end_s(temp, 'l'))
		{
			strcpy(step5, temp);
			strcpy(step5, substring_return(step5, 1));
			if (degree_m(step5) > 1) {
				temp[length - 1] = '\0';
				word = temp;
			}
		}
	}
	
	return word;
}
char* substring_return(char* string, int length) 
{
	char subs[40];
	if (strlen(string) < length)
		return NULL;
	strcpy(subs, string);
	subs[strlen(string) - length] = '\0';
	
	return subs;
}
