# include "mydefine.h"

void handlesource(char *source, char *wordbook)
{
	int initials[26] = { 0 };	
	//must initialize array, or will get wrong values

	int i = 0;

	FILE *f;
	myfopen(&f, source, "r", "handlesource");

	//get imformation of source file
	struct stat st;
	stat(source, &st);

	char *info = NULL;
	info = (char *)calloc(1, sizeof(char) * st.st_size);
	char *endaddr = info + sizeof(char) * st.st_size;
	fread(info, sizeof(char) * st.st_size, 1, f);
	ferror(f);

	countInitials(initials, info, endaddr);	
	//statistic the number of vocabularies under the specific initials(26 initials: a ~ z) 

	Voc **voc;
	voc = (Voc **)calloc(26, sizeof(Voc *));
	//correct usage, it needs 8 (sizeof(struct Vocabuary *) = 8) bytes per pointer
	//sizeof(Voc *) = 8, because it is a pointer

	for(i=0; i<26; i++)
		if(initials[i] != 0)
			voc[i] = (Voc *)calloc(initials[i], sizeof(Voc));	

	classify(voc, initials, info, endaddr);
	//classify vocabularies by its initials

	sort(voc, initials);
	//sort vocabularies through qsort

	writeinfo(voc, initials, wordbook);
	//write message into disk

	for(i=0; i<26; i++)
		if(initials[i] != 0)
			free(voc[i]);

	free(voc);
	free(info);
	fclose(f);
}
