#include "mydefine.h"

int string_cmp(const void *a, const void *b) 
{ 
    Voc *ia = (Voc *)a;
    Voc *ib = (Voc *)b;
    return strcmp(ia->source, ib->source);
} 

void sort(Voc **voc, int *initials)
{
	for(int i=0; i<26; i++)
		qsort(*(voc + i), initials[i], sizeof(Voc), string_cmp);	
}
