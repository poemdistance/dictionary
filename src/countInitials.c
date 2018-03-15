#include "mydefine.h"

void  countInitials(int *initials, char *info, char *endaddr)
{
	int n = 0;
	char *p = info;	

	while(1)
	{
		while((n = getindex(*p)) < 0)
			p++;

		initials[n]++;

		while(*p++ != '\n');

		if(p == endaddr)
			break;
	}
}
