#include "mydefine.h"

void myfopen(FILE **fp, char *name, char *mode, char *funcname)
{

	FILE *log = NULL;
	char logfile[] = "./.log";

	log = fopen(logfile, "a");
	assert(log != NULL);

	if(strcmp(mode, "w") == 0)
	{
		if((*fp = fopen(name, mode)) == NULL)
		{
			fprintf(log, "Create %s file  failed in function %s\n", name, funcname);
			exit(1);
		}

	}

	else if(strcmp(mode, "exist_judge") == 0)
	{
		if(access(name, F_OK) != 0)
		{
			if((*fp = fopen(name, "w")) == NULL)
			{
				fprintf(log, "Create %s file  failed in function %s\n", name, funcname);
				exit(1);
			}
		}
		else 
			fprintf(log, "%s exit, will not create it\n", name);

	}

	else if(strcmp(mode, "r") == 0)
	{
		if(access(name, F_OK) != 0)
		{
			printf("%s file not exist\n", name);
			exit(1);
		}

		if((*fp = fopen(name, mode)) == NULL)
		{
			fprintf(log, "Read %s file  failed in function %s\n", name, funcname);
			exit(1);
		}
	}

	else if(strcmp(mode, "a") == 0)
	{

		if(access(name, F_OK) != 0)
		{
			if((*fp = fopen(name, "w")) == NULL)
			{
				fprintf(log, "Create %s file  failed in function %s\n", name, funcname);
				exit(1);
			}
		}

		else
		{
			if((*fp = fopen(name, mode)) == NULL)
			{
				fprintf(log, "Create %s file  failed in function %s\n", name, funcname);
				exit(1);
			}
		}
	}

	if(*fp != NULL)
		fprintf(log, "function %s, open %s \'%s\' successful\n", funcname, name, mode);

	fclose(log);
}
