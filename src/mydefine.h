#ifndef __MYDEFINE_H__
#define __MYDEFINE_H__

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define RESULT_NUM 50
#define WORD_LENGTH 30
#define TRANS_LENGTH 200

typedef struct Storage Stor;
typedef struct Vocabularies Voc;

struct Vocabularies
{
	char source[WORD_LENGTH];
	char trans[TRANS_LENGTH];
};

extern int getindex(char initials);
extern void countInitials(int *initials, char *info, char *endaddr);
extern void classify(Voc **voc, int *initials, char *info, char *endaddr);
extern void sort(Voc **voc, int *initials);
extern void print(Voc **voc, int *initials);
extern void writeinfo(Voc **voc, int *initials, char *source);
extern void handlesource(char *source, char *wordbook);
extern void readin(Voc ***voc, int *initials, char *wordbook);
extern void search(Voc **voc, int *initials, char *word, int *num, Voc ***result, int *sure);
extern void storage(Voc *result, char ***stor, int *lines, char **buff, char *stor_book);
extern void loadstorage(char ***word, int *initials, int *lines, char *stor_book);
extern void myfopen(FILE **fp, char *name, char *mode, char *funcname);
extern void print_initials(int *initials);
extern void print_max_trans(Voc **voc, int *initials);

#endif
