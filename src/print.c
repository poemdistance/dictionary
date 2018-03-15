#include "mydefine.h"

int numsort(const void *a, const void *b)
{
	int *ia = (int *)a;
	int *ib = (int *)b;

	return *ia > *ib;
}

void print_max_trans(Voc **voc, int *initials)
{
	int i = 0, j = 0;
	int max = 0;
	char *p = NULL;
	char *temp = NULL;
	int length = 0;
	int num = 0;

	for(i=0; i<26; i++)
			num = num + initials[i];

	int *anum = NULL;
	int n = 0;

	anum = (int *)calloc(num, sizeof(int));
	assert(anum != NULL);

	for(i=0; i<26; i++)
	{
		for(j=0; j<initials[i]; j++)
		{
			p = voc[i][j].trans;
			length = 0;

			while(*p++ != '\0')
				length++;

			anum[n++] = length;
			if(length > max)
			{
				max = length;
				temp = voc[i][j].trans;
			}
		}
	}

	assert(p != NULL);
	assert(temp != NULL);
	printf("max trans = %d name = %s\n", max, temp);

	qsort(anum, num, sizeof(int), numsort);
	for(int i=0; i<num; i++)
		printf("anum[%d] = %d\n", i, anum[i]);

}

void print(Voc **voc, int *initials)
{

	int i = 0;
	int j = 0;
	int max = 0;
	int min = 0;
	int num = 0;
	char *p;
	for(i=0; i<26; i++)
	{
		for(j=0; j<initials[i]; j++)
		{
			p = voc[i][j].trans;
			while(*p)
			{
				if(*p >= ' ' && *p <= '~')
					*p = ' ';
				p++;
			}
			p = voc[i][j].trans;
			while(*p)
			{
				if(*p != ' ')
					num = (int)*p;

				if(num > max)
					max = num;
				if(num < min)
					min = num;

				if(min == 0)
					printf("%c\n", *p);
				p++;
			}
		}
	}

	printf("min = %d\n", min);
	printf("max = %d\n", max);
}

void print_initials(int *initials)
{
	int num = 0;
	for(int i=0; i<26; i++)
	{
		num = num + initials[i];
		printf("%c = %d\n", i+65, initials[i]);
	}
	printf("num = %d\n", num);
}

/*calculate the max length of vocaburaries*/
void maxlen(Voc **voc, int *initials)
{
	int i = 0;
	int j = 0;
	int max = 0;
	int n = 0;

	char *word = NULL;

	for(i=0; i<26; i++)
		for(j=0; j<initials[i]; j++)
			if((n = strlen(voc[i][j].source)) > max)
			{
				word = voc[i][j].source;
				max = n;
			}

	printf("max length = %d word is %s\n", max, word);
}
