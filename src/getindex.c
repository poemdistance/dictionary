#include "mydefine.h"

int getindex(char initials)
{
	int index = -1;

	if(initials>='a' && initials<='z')
		index = initials - 'a';

	else if(initials>='A' && initials<='Z')
		index = initials - 'A';

	/*let the words that begin with special character storaged in "x" memory*/
	else if(initials >= '0' && initials <= '9')
		index = 23;

	else if(initials == '&')
		index = 23;

	return index;
}
