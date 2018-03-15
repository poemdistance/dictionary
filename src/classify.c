#include "mydefine.h"

/*
 * This function might be a little hard to understand, because I have imagined
 * some extremely condition and try to handle it. Such as to deal with the source 
 * file that some lines do not have translation, just have word and end with '\n' 
 * or '\r\t\n' and other complex builddup. Also I have handle the word start with
 * '\r' '\t' '\n' and other possible builddup  
 * */

void classify(Voc **voc, int *initials, char *info, char *endaddr)
{

	char *p = info;	
	char *s = NULL;		//voc[i][j].source pointer
	char *t = NULL;		//voc[i][j].trans pointer
	int i = 0;
	int j = 0;

	int copyInitials[26] = { 0 };


	for(i=0; i<26; i++)
		copyInitials[i] = initials[i];
		//use to calculate the 2nd index of voc

	while(1)
	{
		//let pointer point the head of valid word
		while((i = getindex(*p)) < 0)
			p++;

		s = p ;
		j = initials[i] - copyInitials[i];
		copyInitials[i]--;

		//exclude the word which have only one letter
		if(*p == '\n')
			*p = '\0';

		//start to separate word and its translation
		while(1)
		{
			if(*p == ' ' || *p == '\t')
			{
				*p++ = '\0';	//add a mark of ending of word

				//skip the space and tab characters
				while(*p == '\t' || *p == ' ')	
					p++;

				/*if it's '\n' character after the space or tab character we first meet
				 *it is no doubt that *p is a word with no translation, just break here*/
				if(*p == '\n')
					break;

				//or separate the translation here
				t = p;
				while(*p++ != '\n');
				p--;
				*p = '\0';
				strcpy(voc[i][j].trans, t);
				break;
			}

			p++;

			/*if didn't find any tab of space character, mean that it is also a word 
			 *with no translation, just add a mark of ending and then break*/
			if(*p == '\n')
			{
				*p = '\0';
				break;
			}	
		}

		strcpy(voc[i][j].source, s);

		//break the loop if we reach the end of the memory we apply for
		if((p+1) == endaddr)
			break;
	}
}
