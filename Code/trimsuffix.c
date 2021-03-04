#include <stdio.h>
#include "suffix.h"
#include "PATH.h"

int index;
char * word = NULL , *str;
char subs[SIZE];

/***************************************************************************
Function name: trim_suffix
Purpose: This function takes the input as a string and return the root word.
****************************************************************************/

void  trim_suffix(char* word)
{
	char root[SIZE];
	str = (char*)malloc(sizeof(char*) * strlen(word));
	str = return_str(word);
	if (strcmp(str, word) == 0)
		printf("\n\n\t\t\t\t  Suffix can not be removed in the given word.... ");
	else

	printf("\n\t\t\t\t  Word After Removing Suffix is :  %s", str);

}

/**************************************************************************************
Function name: return_str
Purpose: Checking different condition by calling functions included in different steps.
***************************************************************************************/

char* return_str(char* word)
{
	//creating a temporary variable which will be holding value of word variable.
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

/**********************************************************
Function name: cons
Purpose: Check characters in string is vowel or consonant.
***********************************************************/

int cons(int index, char* str)
{
	//If entered word is containing any vowel then it will return FALSE, otherwise TRUE.
	if (str[index] == 'a' || str[index] == 'e' || str[index] == 'i' || str[index] == 'o' || str[index] == 'u')
	{
		return FALSE;
	}
	else
		return TRUE;
}

/****************************************************
Function name: degree_m
Purpose: 1. To count the value of m
		 2. m=vc (occurance of vowel and consonant)
*****************************************************/

int degree_m(char* str)
{
	int count = 0;
	int length;
	length = strlen(str);
	for (index = 0; index < length - 1; index++)
	{
		//Checking Vowel character.
		if (!cons(index, str))
		{
			//Checking Consonant right after the vowel.
			if (cons(index + 1, str) && length > 0)
			{
				count++;
			}
		}
	}
	return count;
}

/**********************************************
Function name: vowel_stem
Purpose: Check if stem contains vowel or not
***********************************************/

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
	//Return '1' if string contains a vowel, '0' otherwise.
	return flag;
}

/**********************************************************
Function name: cons
Purpose: Check if stem ends with double consonant or not.
***********************************************************/

int double_cons(char* str) {
	int length;
	length = strlen(str);
	if (cons(length - 1, str) && str[length - 1] == str[length - 2])
	{
		return 1;
	}
	return 0;
}

/*****************************************************************************
Function name: cons_vowel_cons
Purpose: Check if stem ends with cvc(occurance of consonant vowel consonant).
******************************************************************************/

int cons_vowel_cons(char* str) {
	int length;
	char ch;
	length = strlen(str);
	ch = str[length - 1];

	//Checking the last three characters of string as consonant_vowel_consonant.
	if (cons(length - 1, str) && !cons(length - 2, str) && cons(length - 3, str))
	{

		//Checking the last character of consonant should not be 'w' , 'x' or 'y'.
		if (ch == 'w' || ch == 'x' || ch == 'y')
			return 0;
		return 1;
	}
	return 0;
}

/***********************************************
Function name: end_s
Purpose: Check stem ends with character or not
************************************************/

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

/*************************************************************************************************************************
Function name: cleanup_1
Purpose: 1. If word ends with 'at' then replace with 'ate'.
	 2. If word ends with 'bl' then replace with 'ble'.
	 3. If word ends with double consonant and not ends with 'l','s','z' then replace double consonant with single letter.
***************************************************************************************************************************/

char* cleanup_1(char* string1ab)
{
	int length;
	length = strlen(string1ab);

	//Checking the last two character of string are 'at'.
	if (string1ab[length - 1] == 't' && string1ab[length - 2] == 'a')
	{
		string1ab[length] = 'e';
		string1ab[length + 1] = '\0';

	}

	//Checking the last two character of string are 'b' and 'l'.
	else if (string1ab[length - 1] == 'l' && string1ab[length - 2] == 'b')
	{
		string1ab[length] = 'e';
		string1ab[length + 1] = '\0';

	}

	//Checking the last character of string should not end with 'l','s' or 'z' and satisfy the double consonant condition.
	else if (!(end_s(string1ab, 'l') || end_s(string1ab, 's') || end_s(string1ab, 'z')) && double_cons(string1ab))
	{
		string1ab[length - 1] = '\0';

	}

	//Checking the degree of m should equal to '1' and satisfy the consonant_vowel_consonant condition.
	else if (degree_m(string1ab) == 1 && cons_vowel_cons(string1ab))
	{

		string1ab[length] = 'e';
		string1ab[length + 1] = '\0';
	}

	return string1ab;
}


/*********************************************************************************
Function name: step1_a_b
Purpose: 1. If word ends with 'sses' then replace it with 'ss'
	 2. If word ends with 'ies' then replace with 'i'
	 3. If word ends with 's' then replace with 'NULL'
	 4. If value of m>1 and word ends with 'eed' then replace with 'ee'
	 5. If stem contains vowel and stem ends with 'ed' then replace with 'NULL'
	 6. If stem contains vowel and stem ends with 'ing' then replace with 'NULL'
	 7. Call cleanup_1()
************************************************************************************/


char* step1_a_b(char* temp)
{
	word = NULL;
	int length;
	length = strlen(temp);

	//Checking the last character of string is 's'.
	if (end_s(temp, 's'))
	{

		//Checking the last two characters of string are 'i' and 'e'.
		if (temp[length - 2] == 'e' && temp[length - 3] == 'i')
		{
			temp[length - 2] = '\0';
			word = temp;
		}

		//Checking the last three characters of string are 's','s' and 'e'.
		else if (temp[length - 2] == 'e' && temp[length - 3] == 's' && temp[length - 4] == 's')
		{
			temp[length - 2] = '\0';
			word = temp;
		}

		//Checking the last character of string is 's'.
		else if (temp[length - 2] == 's' && temp[length-3]!='e' && temp[length - 3] != 'n')
		{
			temp[length - 1] = '\0';
			word = temp;

		}
		
	}

	//Checking the last three characters of string are 'e','e' and 'd'.
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

	//Checking the last two characters of string are 'e' and 'd'.
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

	//Checking the last three characters of string are 'i','n' and 'g'.
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

/***********************************************************************************
Function name: step_1_c
Purpose: 1. If stem contains vowel and stem ends with 'y' then replace it with 'i'
************************************************************************************/

char* step_1_c(char* temp)
{
	word = NULL;
	int length;
	length = strlen(temp);

	//Checking the presence of vowel and string ends with 'y'.
	if (vowel_stem(temp) && temp[length - 1] == 'y')
	{
		temp[length - 1] = 'i';
		temp[length] = '\0';
		word = temp;
	}
	
	return word;
}

/**********************************************************************************
Function name: step_2
Purpose: 1. If value of m>0 and word ends with 'ational' then replace with 'ate'
		 2.  If value of m>0 and word ends with 'ization' then replace with 'ize'
		 3.  If value of m>0 and word ends with 'bilite' then replace with 'ble'

***********************************************************************************/

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

		//Checking the degree of m>0 and string ends with 'tional'.
		if ((temp[length - 1] == 'l' && temp[length - 2] == 'a' &&
			temp[length - 3] == 'n' && temp[length - 4] == 'o' &&
			temp[length - 5] == 'i' && temp[length - 6] == 't') || (temp[length - 1] == 'l' && temp[length - 2] == 'a'))
		{
			strcpy(step2, temp);
			strcpy(step2, substring_return(step2, 2));
			if (degree_m(step2) > 0) {
				temp[length - 2] = '\0';
				word = temp;
			}
		}

		//Checking the degree of m>0 and string ends with 'ization'.
		else if ((length > 7 && degree_m(step2) > 0) &&
			(temp[length - 1] == 'n' && temp[length - 2] == 'o' &&
				temp[length - 3] == 'i' && temp[length - 4] == 't' &&
				temp[length - 5] == 'a' && temp[length - 6] == 'z' && temp[length - 7] == 'i'))
		{
			temp[length - 5] = 'e';
			temp[length - 4] = '\0';
			word = temp;
		}


		//Checking the string ends with 'biliti'.

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

/*********************************************************************************
Function name: step_3
Purpose: 1. If value of m>0 and word ends with 'icate' then replace with 'ic'
		 2. If value of m>0 and word ends with 'ful' then replace with 'NULL'
		 3. If value of m>0 and word ends with 'ness' then replace with 'NULL'
***********************************************************************************/

char* step_3(char* temp) {
	word = NULL;
	int length = strlen(temp);
	char step3[30];
	strcpy(step3, temp);

	//Checking the string ends with 'ful'.
	if (temp[length - 1] == 'l' && temp[length - 2] == 'u' && temp[length - 3] == 'f')
	{
		strcpy(step3, substring_return(step3, 3));
		if (degree_m(step3) > 0)	
		{
			temp[length - 3] = '\0';
			word = temp;
		}

	}

	//Checking the string ends with 'ness'.
	if (temp[length - 1] == 's' && temp[length - 2] == 's' && temp[length - 3] == 'e' && temp[length - 4] == 'n')
	{
		strcpy(step3, substring_return(step3, 4));
		if (degree_m(step3) > 0)	
		{
			temp[length - 4] = '\0';
			word = temp;
			
		}

	}

	//Checking the string ends with 'icate'.
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

/*******************************************************************************
Function name: step_4
Purpose: 1. If value of m>0 and word ends with 'ance' then replace with 'NULL'
		 2. If value of m>0 and word ends with 'ent' then replace with 'NULL'
		 3. If value of m>0 and word ends with 'ive' then replace with 'NULL'
********************************************************************************/


char* step_4(char* temp) {
	word = NULL;

	int length = strlen(temp);
	char step4[30];
	strcpy(step4, temp);
	if (strlen(step4) > 4) {

		strcpy(step4, substring_return(step4, 4));

		//Checking the length of string and m>0 and string ends with 'ance'.
		if ((length > 4 && degree_m(step4) > 0) &&
			(temp[length - 1] == 'e' && temp[length - 2] == 'c' &&
				temp[length - 3] == 'n' && temp[length - 4] == 'a'))
		{
			temp[length - 4] = '\0';
			word = temp;
		}

		//Checking the length of string and string ends with 'ent'.
		else if (length > 3 && temp[length - 1] == 't' && temp[length - 2] == 'n' && temp[length - 3] == 'e')
		{
			strcpy(step4, temp);
			strcpy(step4, substring_return(step4, 3));
			if (degree_m(step4) > 0) {
				temp[length - 3] = '\0';
				word = temp;
			}
		}

		//Checking the length of string and string ends with 'ive'.
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

/****************************************************************************************************************
Function name: step_5
Purpose: 1. If value of m>1 and word ends with 'e' then replace with 'NULL'.
		 2. If value of m=0 and in end word not contain cvc form and ends with 'ness' then replace with 'NULL'.
		 3. If m>1 and word ends with double consonant and word ends with 'l' then it replace with single letter.
******************************************************************************************************************/


char* step_5(char* temp)
{
	word = NULL;
	int length = strlen(temp);
	char step5[30];
	strcpy(step5, temp);
	if (strlen(step5) > 4) {
		strcpy(step5, substring_return(step5, 1));

		//Checking the degree m>1 and string ends with 'e'.
		if (length > 1 && degree_m(step5) > 1 && (temp[length - 1] == 'e'))
		{
			temp[length - 1] = '\0';
			word = temp;
		}

		//Checking string end with 'ness'.
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


		//Checking degree of m>1 and string ends with double consonant and ends with 'l'.
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

/*********************************************************************************
Function name: substring_return
Purpose: It will return the string of specified length given by 'length' variable.
**********************************************************************************/

char* substring_return(char* string, int length) 
{
	
	if (strlen(string) < length)
		return NULL;
	strcpy(subs, string);
	subs[strlen(string) - length] = '\0';
	
	return subs;
}
