#include "mydefine.h"

/*It is a function which can read the imformation from file ".wordbook" and storage it 
 *to the struct vocabularies(Voc) in memory we calloc*/

void readin(Voc ***voc, int *initials, char *wordbook)
{
	FILE *fpw = NULL;
	int i = 0;

	//Open the file as read only mode
	myfopen(&fpw, wordbook, "r", "readin");

	//first read the initials imformation from ".wordbook" and storage it
	if(fread(initials, sizeof(int), 26, fpw) <= 0)
	{
		printf("read error in readin function\n");
		exit(1);
	}

	//calloc memory
	*voc = (Voc **)calloc(26, sizeof(Voc *));
	assert(*voc != NULL);

	for(i=0; i<26; i++)
	{
		(*voc)[i] = (Voc *)calloc(initials[i], sizeof(Voc));
		if(initials[i] != 0)
			assert((*voc)[i] != NULL);
	}

	for(i=0; i<26; i++)
	{
		//read the imformation into the struct
		if(fread((*voc)[i], sizeof(Voc), initials[i], fpw) != initials[i])
		{
			printf("read error in readin function\n");
			exit(1);
		}
	}

	fclose(fpw);
}
