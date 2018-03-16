#include "mydefine.h"

/*write the relevant information to disk
 * (initials & struct vocabularies: source, trans)
 * */

void writeinfo(Voc **voc, int *initials, char *wordbook)
{
	FILE *fpw = NULL;
	int i = 0;

	myfopen(&fpw, wordbook, "w", "writeinfo");
	assert(fpw != NULL);
	
	//record the number of vocabulary under the specific initials
	if(fwrite(initials, sizeof(int), 26, fpw) <= 0)
	{
		printf("write error\n");
		exit(1);
	}

	for(i=0; i<26; i++)
	{
			if(fwrite(voc[i], sizeof(Voc), initials[i], fpw) != initials[i])
			{
				printf("write error when write %s\n", voc[i][0].source);
				exit(1);
			}
	}

	fclose(fpw);
}
