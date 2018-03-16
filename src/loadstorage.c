#include "mydefine.h"

void loadstorage(char ***stor, int *initials, int *lines, char *stor_book)
{
	FILE *fp = NULL;
	//char stor_book[20] = "source";	//test code
	int i = 0;
	int flag = 1;

	/*Judge whether the file is exist or not, 
	 * if it doesn't exist, create it*/
	myfopen(&fp, stor_book, "exist_judge", "loadstorage");

	/*If stor_book file is exist, it will not be created and opened,
	 *if so, fp will be NULL, do not close the file which didn't be opened */
	if(fp != NULL)
		fclose(fp);

	myfopen(&fp, stor_book, "r", "loadstorage");

	*stor = (char **)calloc(200, sizeof(char *));
	for(i=0; i<200; i++)
		(*stor)[i] = (char *)calloc(1, sizeof(char)*50);

	rewind(fp);

	char temp[500];
	char *p = temp;
	memset(temp, 0, sizeof(temp));

	while(fgets(temp, sizeof(temp), fp) != NULL)
	{
		for(i=0; i<2; i++)
			if(getindex(temp[i]) == -1)
				continue;
			else break;

		if(i >= 2)
			continue;

		(*lines)++;

		p = temp;
		while(getindex(*p++) != -1);
		*(p-1) = '\0';

		if((*lines % 200) == 0)
		{
			flag++;
			*stor = (char **)realloc(*stor, sizeof(char *) * 200 * flag);
			for(i=200 * (flag-1); i<*lines+200; i++)
				(*stor)[i] = (char *)calloc(1, sizeof(char) * WORD_LENGTH);
		}

		i = *lines;
		strcpy( (*stor)[i-1], temp);
	}

	ferror(fp);
	fclose(fp);
}
