#include <stdio.h>
#include <errno.h>

void error_handler(char *func_name)
{
	printf("Error while %s returned errorno: %d\n", func_name, errno);
	exit(-1);
}