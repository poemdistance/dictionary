#include "mydefine.h"

//if there is not match any word in ".wordbook", search the similar words here
void swsearch(Voc **voc, int *initials, char *word, Voc ***result, int *num)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int n = 0;
	int flag = 0;
	int len = strlen(word);

	//useing it to measure the difference between the "word" and other words
	int diff = 0;

	//The difference betweent the length of "word" and other words'
	int difflen = 0;

	char *p = word;
	char *s = NULL;

	assert(p != NULL);

	if(len >= 2)
		for(i=0; i<26; i++)
		{
			for(j=0; j<initials[i]; j++)
			{
				diff = 0;	//clear diff with 0
				p = word;	//let the pointer point the start of word
				s = voc[i][j].source;

				difflen = strlen(voc[i][j].source) - len;
				difflen = abs(difflen);

				/*if the length of word is too short, to avoid 
				 *too many unnecessary vocabularies being found
				 * let difflen+*/ 
				if(len <= 3)
					difflen += 2;

				if(difflen <= 2)
				{

					for(k=0; k<len; k++)
					{
						if(diff <= 2)
						{
							//if the character is different between each other, let diff++
							if(getindex(*s) != getindex(*p))
								diff++;
						}
						else
							break;
						p++;
						s++;
					}

					if(diff <= 1)
					{
						flag = 1;
						if(n == RESULT_NUM)		//Todo
						{
							printf("too many similar words, n out of range\n");
							n = 19;	
						}

						/*Copy the whole struct to result,
						 * do not copy the pointer to it, all memory in this function
						 * will be freed after the end of this function*/
						(*result)[n++][0] = voc[i][j];
					}
				}
			}
		}
	if(flag == 1)
		*num = n - 1;
}


void search_en(Voc **voc, int *initials, char *word, int n, Voc ***result, int *num, int *sure)
{
	int i = 0;
	int low = 0;
	int high = initials[n] - 1;
	int mid;
	int flag = 0;

	while(low <= high)
	{
		mid = (low + high) / 2;

		if(strcmp(word, voc[n][mid].source) == 0)
		{
			printf("\t%s\t%s\n", voc[n][mid].source, voc[n][mid].trans);
			flag = 1;
			*num = 1;
			*sure = 1;
			strcpy((*result)[0]->source, voc[n][mid].source);
			strcpy((*result)[0]->trans, voc[n][mid].trans);
			break;
		}

		if(strcmp(word, voc[n][mid].source) < 0)
			high = mid - 1;

		else if(strcmp(word, voc[n][mid].source) > 0)
			low = mid + 1;
	}

	//if not found the match word, search similar word hear
	if(!flag)
	{
		swsearch(voc, initials, word, result, num);

		for(i=0; i<*num; i++)
		{

			if(!flag)
			{
				flag = 1; 
				printf("\n %s didn't find. Did you mean: ", word);
			}
			printf("\n\t%d: %s\t%s\n", i, (*result)[i]->source, (*result)[i]->trans);
		}

		if(!flag)
			printf("\t%s not found\n", word);
	}

}

void search_zh(Voc **voc, int *initials, char *word,int n, Voc ***result, int *num)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int find = 0;
	int length = 0;
	char *str = NULL;
	char *p = NULL;
	int difflen = 0;

	for(i=0; i<26; i++)
	{
		for(j=0; j<initials[i]; j++)
		{
			if((str = (strstr(voc[i][j].trans, word))) != NULL)
			{
				length = 0;

				p = str;
				while(*p-- < 0)
					length++;

				p = str;
				while(*p++ < 0)
					length++;	//calculete the length of match translation

				difflen = strlen(word) - length;
				difflen = abs(difflen);

				if(strlen(word) <= 4)
					difflen += 2;

				//filter some words
				if(difflen <= 3)
				{
					printf("\t%d: %s\t%s\n",k, voc[i][j].source, voc[i][j].trans);
					(*result)[k++][0] = voc[i][j];
					find = 1;

					if(k >= RESULT_NUM) //todo
					{
						k = 20;
						printf("too many match word, out of bound\n");
					}
				}
			}
		}
	}

	if(find == 0)
		printf("Not Found\n");
	else 
		*num = k - 1;
}

void search(Voc **voc, int *initials, char *word, int *num, Voc ***result, int *sure)
{
	char *p = word;
	int n = 0;

	while(1)
	{
		n = getindex(*p);
		if((n >= 0 && n <= 26) || *p < 0)
			break;
		p++;

		if(*p == '\n')
		{
			*num = 0;
			return;
		}
	}

	word = p;

	while(*p++ != '\n');
	*--p = '\0';

	*num = 0;
	if(*word >= 0)
		search_en(voc, initials, word, n, result, num, sure);

	else 
		search_zh(voc, initials, word, n, result, num);

}
