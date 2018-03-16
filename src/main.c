#include "mydefine.h"

int main(int argc, char **argv)
{

	printf("pid = %ld\n", (long)getpid());

	struct timespec start, finish;

	if(clock_gettime(CLOCK_REALTIME, &start) == -1)
		printf("Get start time error\n");

	FILE *fpw = NULL;

	/*请自行修改以下三个文件的位置，其中wordbook为将要保存的词典文件位置
	 *由源文件source读入并处理生成; source 为单词源文件，可自行网上下载
	 *也可直接使用word/下的;stor_book为查询后自动保存单词的文件位置
	 */
	char wordbook[] = ".wordbook";
	char source[] = "../word/word";
	char stor_book[] = "./storage";

	int i = 0;
	int flag = 0;
	int num = 0;
	int lines = 0;

	//storage the state of source and output file
	struct stat sts, sto;

	Voc **result = NULL;
	result = (Voc **)calloc(RESULT_NUM, sizeof(Voc *));
	assert(result != NULL);

	for(i=0; i<RESULT_NUM; i++)
		assert((result[i] = (Voc *)calloc(1, sizeof(Voc))) != NULL);

	/*If there is not exit ".workbook" file, create it
	 *else do not do anything*/
	myfopen(&fpw, wordbook, "exist_judge", "main");

	//obtain the imformation to sts & sto
	stat(source, &sts);
	stat(wordbook, &sto);

	/*Calculate the difference of modify time between the source file and the .wordbook's*/
	int difftime = sts.st_mtime - sto.st_mtime;

	/*If .wordbook is empty or source file has been modified after
	 * the generation of .wordbook, execute the below function*/
	if(sto.st_size == 0 || difftime > 0)
		handlesource(source, wordbook);

	//Create Voc to storage the imformation we will read from .workbook 
	Voc **voc = NULL;
	int initials[26] = { 0 };

	//read imformation from .workbook into memory
	readin(&voc, initials, wordbook);

	//judge whether calloc have applied for the memory successfully of not
	//It seems that it is unnecessary, emm, do it fistly
	assert(voc != NULL);
	for(i=0; i<26; i++)
		if(initials[i] != 0)
			assert(voc[i] != NULL);

	//load the vocabularies had storaged in "storage" file
	char **stor = NULL;
	loadstorage(&stor, initials, &lines, stor_book);

	char **buff = NULL;
	buff = (char **)calloc(500, sizeof(char *));
	for(i=0; i<500; i++)
		buff[i] = (char *)calloc(1, sizeof(char) * 50);

	if(clock_gettime(CLOCK_REALTIME, &finish) == -1)
		printf("Get finish time error\n");

	printf("time = %.4f\n", ((1.0 * finish.tv_sec - start.tv_sec) * 1000000000 \
				+ (finish.tv_nsec - start.tv_nsec)) / 1000000000);

	printf("\n>>  ");
	char word[500];

	memset(word, 0, sizeof(word));

	/*Using 'test' to determine whether we should storage word we refer or not,
	 *when add test parameter like this: ./a.out test, it will not storage any word we refer*/
	int test = 1;
	if(argc > 1)
		if(strcmp(argv[1], "test") == 0)
			test = 0;

	int n = 0;
	int sure = 0;
	char *p = NULL;
	while(fgets(word, sizeof(word), stdin))
	{
		if(strcmp(word, "q\n") == 0)
		{
			printf("\n\tThanks for using. Good bye~ ^_^ \n\n");
			break;
		}

		//Check whether input character is '\n' or '/' or not, if so, skip it 
		if(strcmp(word, "\n") == 0 || strcmp(word, "/\n") == 0)
		{
			printf("\n>>  ");
			for(i=0; i<RESULT_NUM; i++)
				memset(result[i], 0, sizeof(Voc));
			continue;
		}

		n = 0;
		flag = 1;
		sure = 0;
		if(strcmp(word, ".\n") == 0)
		{
			sure = 1;
			flag = 0;
		}

		/*judge whether the string is only a number*/
		p = word;
		while(*p != '\n' && flag)
		{
			if(*p >= '0' && *p <= '9')
				p++;
			else 
				break;
		}

		if(*p == '\n' && flag)
		{
			*p = '\0';
			n = atoi(word);
			if(n >= num)
			{
				if(num == 0)
					printf("\tNo result to storage\n");
				else
					printf("\tn out of bound\n");
				printf(">> ");
				continue;
			}
			flag = 0;
			sure = 1;
		}
		else if(sure != 1)
			for(i=0; i<num; i++)
				memset(result[i], 0, sizeof(Voc));

		if(flag)
			search(voc, initials, word, &num, &result, &sure);
		if(sure == 1)
			flag = 0;

		if(num >= 1 && !flag && test && sure)
			storage(result[n], &stor, &lines, buff, stor_book);

		printf("\n>>  ");
		memset(word, 0, sizeof(word));
	}

	for(i=0; i<lines; i++)
		free(stor[i]);
	free(stor);

	for(i=0; i<RESULT_NUM; i++)
		free(result[i]);
	free(result);

	for(i=0; i<26; i++)
		if(initials[i] != 0)
			free(voc[i]);
	free(voc);

	return 0;
}
