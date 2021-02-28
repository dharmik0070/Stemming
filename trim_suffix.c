#include <stdio.h>
#include "prefix.h"
#include "suffix.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
int i;
char* s = NULL;
char* str;

void  trim_suffix(char* s)
{
	FILE* fp1;
	char root[50];
	str = (char*)malloc(sizeof(char*) * strlen(s));
	str = return_str(s);
	if (str == NULL) {
		printf("Nothing returned");
	}
	else {
		fp1 = fopen("C:\\Users\\Dharmik\\Downloads\\stemming\\rootword.txt", "r");
		while (fgets(root, sizeof(root), fp1))
		{
			root[strcspn(root, "\n")] = 0;
			if (strcmp(root, str) == 0)
			{
				printf("\n  Word After Removing Suffix is :  %s", str);
			}
		}
	}

}

char* return_str(char* s)
{
	char* temp;
	temp = (char*)malloc(sizeof(char*));
	strcpy(temp, s);
	step1_a_b(temp);
	step_1_c(temp);
	step_2(temp);
	step_3(temp);
	step_4(temp);
	step_5(temp);
	return s;
}
/*
function name: cons
Purpose: check characters in string is vowel or consonant
*/
int cons(int i, char* str)
{
	if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
	{
		return FALSE;
	}
	else
		return TRUE;
}

/*
function name: degree_m
Purpose: to count the value of m
	      m=vc (occurance of vowel and consonant)
*/
int degree_m(char* str)
{
	int count = 0;
	int length;
	length = strlen(str);
	for (i = 0; i < length - 1; i++)
	{
		if (!cons(i, str))
		{
			if (cons(i + 1, str) && length > 0)
			{
				count++;
			}
		}
	}
	return count;
}

/*
function name: vowel_stem
Purpose: check if stem contains vowel or not
*/
int vowel_stem(char* str)
{
	int flag = 0;
	for (i = 0; str[i]; i++)
	{
		if (!cons(i, str))
		{
			flag = 1;
		}
	}
	return flag;
}

/*
function name: cons
Purpose: check if stem ends with double consonant or not
*/

int double_cons(char* str) {
	int length;
	length = strlen(str);
	if (cons(length - 1, str) && str[length - 1] == str[length - 2])
	{
		return 1;
	}
	return 0;
}

/*
function name: cons
Purpose: check if stem ends with cvc(occurance of consonant vowel consonant)
*/
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

/*
function name: end_s
Purpose: check stem ends with character or not
*/
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

/*
function name: cleanup_1
Purpose: 1. if word ends with 'at' then replace with 'ate'
		 2. if word ends with 'bl' then replace with 'ble'
		 3. if word ends with double consonant and not ends with 'l','s','z' then replace double consonant with single letter
*/

char* cleanup_1(char* sr)
{
	int length;
	length = strlen(sr);
	if (sr[length - 1] == 't' && sr[length - 2] == 'a')
	{
		sr[length] = 'e';
		sr[length + 1] = '\0';

	}
	else if (sr[length - 1] == 'l' && sr[length - 2] == 'b')
	{
		sr[length] = 'e';
		sr[length + 1] = '\0';

	}

	else if (!(end_s(sr, 'l') || end_s(sr, 's') || end_s(sr, 'z')) && double_cons(sr))
	{
		sr[length - 1] = '\0';

	}
	else if (degree_m(sr) == 1 && cons_vowel_cons(sr))
	{

		sr[length] = 'e';
		sr[length + 1] = '\0';
	}
	return sr;
}

/*
function name: step1_a_b
Purpose: 1. if word ends with 'sses' then replace it with 'ss'
		 2. if word ends with 'ies' then replace with 'i'
		 3. if word ends with 's' then replace with 'NULL'
		 4. if value of m>1 and word ends with 'eed' then replace with 'ee'
		 5. if stem contains vowel and stem ends with 'ed' then replace with 'NULL'
		 6. if stem contains vowel and stem ends with 'ing' then replace with 'NULL'
		 7. call cleanup_1()
*/
char* step1_a_b(char* temp)
{
	s = NULL;
	int length;
	length = strlen(temp);
	if (end_s(temp, 's'))
	{
		if (temp[length - 2] == 'e' && temp[length - 3] == 'i')
		{
			temp[length - 2] = '\0';
			s = temp;
		}
		else if (temp[length - 2] == 'e' && temp[length - 3] == 's' && temp[length - 4] == 's')
		{
			temp[length - 2] = '\0';
			s = temp;
		}
		else if (temp[length - 2] == 's')
		{
			s = temp;
		}
		else {
			temp[length - 1] = '\0';
			s = temp;
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
			s = temp;
		}
	}
	else if (temp[length - 1] == 'd' && temp[length - 2] == 'e')
	{

		char ed[30];
		strcpy(ed, temp);
		if (strlen(ed) > 2) {

			strcpy(ed, substring_return(ed, 2));

			if (vowel_stem(ed)) {
				s = cleanup_1(ed);
			}
		}
	}
	else if (temp[length - 1] == 'g' && temp[length - 2] == 'n' && temp[length - 3] == 'i')
	{
		char ing[30];
		strcpy(ing, temp);
		if (strlen(ing) > 3) {

			strcpy(ing, substring_return(ing, 3));

			if (vowel_stem(ing)) {
				s = cleanup_1(ing);
			}
		}

	}
	printf("\n\nIn step 1_a_b, final value of s is %s\n", s);

}
/*
function name: step_1_c
Purpose: 1. if stem contains vowel and stem ends with 'y' then replace it with 'i'		 
*/
char* step_1_c(char* temp)
{
	s = NULL;
	int length;
	length = strlen(temp);
	if (vowel_stem(temp) && temp[length - 1] == 'y')
	{
		temp[length - 1] = 'i';
		temp[length] = '\0';
		s = temp;
	}
	printf("\nIn step 1_c, final value of s is %s\n", s);

}

/*
function name: step_2
Purpose: 1. if value of m>0 and word ends with 'ational' then replace with 'ate'
		 2.  if value of m>0 and word ends with 'ization' then replace with 'ize'
		 3.  if value of m>0 and word ends with 'bilite' then replace with 'ble'
		 
*/

char* step_2(char* temp) {
	s = NULL;
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
			s = temp;
		}
		if (temp[length - 1] == 'l' && temp[length - 2] == 'a' &&
			temp[length - 3] == 'n' && temp[length - 4] == 'o' &&
			temp[length - 5] == 'i' && temp[length - 6] == 't')
		{
			strcpy(step2, temp);
			strcpy(step2, substring_return(step2, 2));
			if (degree_m(step2) > 0) {
				temp[length - 2] = '\0';
				s = temp;
			}
		}
		else if ((length > 7 && degree_m(step2) > 0) &&
			(temp[length - 1] == 'n' && temp[length - 2] == 'o' &&
				temp[length - 3] == 'i' && temp[length - 4] == 't' &&
				temp[length - 5] == 'a' && temp[length - 6] == 'z' && temp[length - 7] == 'i'))
		{
			temp[length - 5] = 'e';
			temp[length - 4] = '\0';
			s = temp;
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
				s = temp;
			}
		}
	}

	printf("\nIn step 2, final value of s is %s\n", s);
}

/*
function name: step_3
Purpose: 1. if value of m>0 and word ends with 'icate' then replace with 'ic'
		 2. if value of m>0 and word ends with 'ful' then replace with 'NULL'
		 3. if value of m>0 and word ends with 'ness' then replace with 'NULL'

*/

char* step_3(char* temp) {
	s = NULL;
	int length = strlen(temp);
	char step3[30];
	strcpy(step3, temp);
	if (strlen(step3) > 5) {

		strcpy(step3, substring_return(step3, 5));
		if ((length > 3 && degree_m(step3) > 0) &&
			(temp[length - 1] == 'e' && temp[length - 2] == 't' &&
				temp[length - 3] == 'a' && temp[length - 4] == 'c' && temp[length - 5] == 'i'))
		{
			temp[length - 3] = '\0';
			s = temp;
		}
		else if ((temp[length - 1] == 'l' && temp[length - 2] == 'u' && temp[length - 3] == 'f'))
		{
			strcpy(step3, temp);
			strcpy(step3, substring_return(step3, 3));
			if (length > 3 && degree_m(step3) > 0) {
				temp[length - 3] = '\0';
				s = temp;
			}

		}
		else if (temp[length - 1] == 's' && temp[length - 2] == 's' &&
			temp[length - 3] == 'e' && temp[length - 4] == 'n')
		{
			strcpy(step3, temp);
			strcpy(step3, substring_return(step3, 4));

			if (length > 4 && degree_m(step3) > 0) {
				temp[length - 4] = '\0';
				s = temp;
			}
		}
	}
	printf("\nIn step 3, final value of s is %s\n", s);
}
/*
function name: step_4
Purpose: 1. if value of m>0 and word ends with 'ance' then replace with 'NULL'
		 2. if value of m>0 and word ends with 'ent' then replace with 'NULL'
		 3. if value of m>0 and word ends with 'ive' then replace with 'NULL'

*/

char* step_4(char* temp) {
	s = NULL;

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
			s = temp;
		}
		else if (length > 3 && temp[length - 1] == 't' && temp[length - 2] == 'n' && temp[length - 3] == 'e')
		{
			strcpy(step4, temp);
			strcpy(step4, substring_return(step4, 3));
			if (degree_m(step4) > 0) {
				temp[length - 3] = '\0';
				s = temp;
			}
		}
		else if (length > 3 && temp[length - 1] == 'e' && temp[length - 2] == 'v' && temp[length - 3] == 'i')
		{
			strcpy(step4, temp);
			strcpy(step4, substring_return(step4, 3));
			if (degree_m(step4) > 0) {
				temp[length - 3] = '\0';
				s = temp;
			}
		}
	}
	printf("\nIn step 4, final value of s is %s\n", s);

}

/*
function name: step_5
Purpose: 1. if value of m>1 and word ends with 'e' then replace with 'NULL'
		 2. if value of m=0 and in end word not contain cvc form and ends with 'ness' then replace with 'NULL'
		 3. if m>1 and word ends with double consonant and word ends with 'l' then it replace with single letter
*/

char* step_5(char* temp)
{
	s = NULL;
	int length = strlen(temp);
	char step5[30];
	strcpy(step5, temp);
	if (strlen(step5) > 4) {
		strcpy(step5, substring_return(step5, 1));
		if (length > 1 && degree_m(step5) > 1 && (temp[length - 1] == 'e'))
		{
			temp[length - 1] = '\0';
			s = temp;
		}
		else if (length > 4 && end_s(temp, 's') && (temp[length - 2] == 's') &&
			(temp[length - 3] == 'e') && (temp[length - 4] == 'n'))
		{
			strcpy(step5, temp);
			strcpy(step5, substring_return(step5, 4));
			if (degree_m(step5) == 1 && !cons_vowel_cons(step5)) {
				temp[length - 4] = '\0';
				s = temp;
			}
		}

		else if (length > 2 && double_cons(temp) && end_s(temp, 'l'))
		{
			strcpy(step5, temp);
			strcpy(step5, substring_return(step5, 1));
			if (degree_m(step5) > 1) {
				temp[length - 1] = '\0';
				s = temp;
			}
		}
	}
	printf("\nIn step 5, final value of s is %s\n", s);

}
/*
function name: substring_return
Purpose: 

*/

char* substring_return(char* st, int len) {
	char subs[40];
	if (strlen(st) < len)
		return NULL;
	strcpy(subs, st);
	subs[strlen(st) - len] = '\0';
	return subs;
}