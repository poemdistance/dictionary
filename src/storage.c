#include "mydefine.h"

/*
 *to save words in time, prevent having not save words cause by the interrupt of program, 
 *do not just only save it to the memory at first and then write into disk when quit the 
 *program
 * */

void storage(Voc *result, char ***stor, int *lines, char **buf, char *stor_book)
{

	int i = 0;
	int num = 0;

	for(i=0; i<*lines; i++)
	{
		if(strcmp((*stor)[i], result->source) == 0)
		{
			printf("\tYou have storaged this word before\n");
			return;
		}
	}

	FILE *fp = NULL;

	myfopen(&fp, stor_book, "a", "storage");

	if(fprintf(fp, "%s\t%s\n", result->source, result->trans) < 0)
		printf("write error in storage function, let it go\n");
	else 
	{
		//printf("\tstoraged '%s' successful\n", result->source);

		/*plus 1 to avoid to apply for the memory duplicately when the number of lines
		 *is just 200, 400...*/
		(*lines)++;

		if(*lines % 200 == 0)
		{
			num = *lines / 200 + 1;
			*stor = (char **)realloc(*stor, sizeof(char *) * 200 * num);
			for(i=200 * (num-1); i<*lines+200; i++)
				(*stor)[i] = (char *)calloc(1, sizeof(char) * WORD_LENGTH);
		}

		i = *lines - 1;

		//storage the new word to 'stor'
		strcpy((*stor)[i], result->source);
	}

	fclose(fp);
}
