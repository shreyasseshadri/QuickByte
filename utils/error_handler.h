#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void error_handler(char *func_name)
{	
	if(errno != 0)
	{
		printf("Error while %s returned errorno: %d\n", func_name, errno);
		exit(-1);		
	}
}