#include "mydefine.h"

/*
 *to save words in time, prevent having not save words cause by the interrupt of program, 
 *do not just only save it to the memory at first and then write into disk when quit the 
 *program
 * */

void storage(Voc *result, char **stor, int *lines, char **buf, char *stor_book)
{

	int i = 0;

	for(i=0; i<*lines; i++)
	{
		if(strcmp(stor[i], result->source) == 0)
		{
			printf("\n\tYou have storaged this word before\n");
			return;
		}
	}

	FILE *fp = NULL;

	myfopen(&fp, stor_book, "a", "storage");

	if(fprintf(fp, "%s\t%s\n", result->source, result->trans) < 0)
		printf("write error in storage function, let it go\n");
	else 
		printf("\tstoraged '%s' successful\n", result->source);

	fclose(fp);
}
